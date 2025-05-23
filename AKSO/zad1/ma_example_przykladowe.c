#ifdef NDEBUG
#undef NDEBUG
#endif

#include "ma.h"
#include "memory_tests.h"
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/** MAKRA SKRACAJĄCE IMPLEMENTACJĘ TESTÓW **/

// To są możliwe wyniki testu.
#define PASS 0
#define FAIL 1
#define WRONG_TEST 2

// Oblicza liczbę elementów tablicy x.
#define SIZE(x) (sizeof x / sizeof x[0])

#define ASSERT(f)                        \
  do {                                   \
    if (!(f))                            \
      return FAIL;                       \
  } while (0)

#define V(code, where) (((unsigned long)code) << (3 * where))

/** WŁAŚCIWE TESTY **/

void t_one(uint64_t *next_state, uint64_t const *input,
           uint64_t const *old_state, size_t, size_t) {
  next_state[0] = old_state[0] + input[0];
}

void y_one(uint64_t *output, uint64_t const *state, size_t, size_t) {
  output[0] = state[0] + 1;
}

static void t_two(uint64_t *next_state, uint64_t const *input,
                  uint64_t const *old_state, size_t, size_t) {
  next_state[0] = old_state[0] ^ input[0];
}

// Testuje jeden automat wykonujący jakieś dodawania.
static int one(void) {
  const uint64_t q1 = 1, x3 = 3, *y;

  moore_t *a = ma_create_full(64, 64, 64, t_one, y_one, &q1);
  assert(a);

  y = ma_get_output(a);
  ASSERT(y != NULL);
  ASSERT(ma_set_input(a, &x3) == 0);
  // printf("%d\n", y[0]);
  ASSERT(y[0] == 2);
  ASSERT(ma_step(&a, 1) == 0);
  // printf("%d\n", y[0]);
  ASSERT(y[0] == 5);
  ASSERT(ma_step(&a, 1) == 0);
  // printf("%d\n", y[0]);
  ASSERT(y[0] == 8);
  ASSERT(ma_set_input(a, &q1) == 0);
  ASSERT(ma_set_state(a, &x3) == 0);
  // printf("%d\n", y[0]);
  ASSERT(y[0] == 4);
  ASSERT(ma_step(&a, 1) == 0);
  // printf("%d\n", y[0]);
  ASSERT(y[0] == 5);
  ASSERT(ma_step(&a, 1) == 0);
  // printf("%d\n", y[0]);
  ASSERT(y[0] == 6);

  ma_delete(a);
  return PASS;
}

// Testuje dwa automaty tworzące dwubitowy licznik binarny.
static int two(void) {
  uint64_t x = 1;
  const uint64_t *y[2];
  moore_t *a[2];

  a[0] = ma_create_simple(1, 1, t_two);
  a[1] = ma_create_simple(1, 1, t_two);
  assert(a[0]);
  assert(a[1]);

  printf("test1\n");

  y[0] = ma_get_output(a[0]);
  y[1] = ma_get_output(a[1]);
  ASSERT(y[0] != NULL);
  ASSERT(y[1] != NULL);

  printf("%d %d\n", y[1][0], y[0][0]);

  printf("test2\n");

  // Na początku licznik ma wartość 00.
  ASSERT(ma_set_input(a[0], &x) == 0);
  ASSERT(ma_connect(a[1], 0, a[0], 0, 1) == 0);
  ASSERT(y[1][0] == 0 && y[0][0] == 0);

  printf("%d %d\n", y[1][0], y[0][0]);

  printf("test3\n");

  // Po jednym kroku licznik ma wartość 01.
  ASSERT(ma_step(a, 2) == 0);


  ASSERT(y[1][0] == 0 && y[0][0] == 1);

  printf("%d %d\n", y[1][0], y[0][0]);

  printf("test4\n");

  // Po dwóch krokach licznik ma wartość 10.
  ASSERT(ma_step(a, 2) == 0);
  ASSERT(y[1][0] == 1 && y[0][0] == 0);

  // Po trzech krokach licznik ma wartość 11.
  ASSERT(ma_step(a, 2) == 0);
  ASSERT(y[1][0] == 1 && y[0][0] == 1);

  // Po czterech krokach licznik ma wartość 00.
  ASSERT(ma_step(a, 2) == 0);
  ASSERT(y[1][0] == 0 && y[0][0] == 0);
  ASSERT(ma_step(a, 2) == 0);

  // Po pięciu krokach licznik ma wartość 01.
  ASSERT(y[1][0] == 0 && y[0][0] == 1);

  printf("test5\n");

  // Po rozłączeniu automatów starczy bit licznika przestaje się zmieniać.
  ASSERT(ma_disconnect(a[1], 0, 1) == 0);

  printf("test6\n");

  x = 0;
  ASSERT(ma_set_input(a[1], &x) == 0);
  ASSERT(ma_step(a, 2) == 0);
  ASSERT(y[1][0] == 0 && y[0][0] == 0);
  ASSERT(ma_step(a, 2) == 0);
  ASSERT(y[1][0] == 0 && y[0][0] == 1);

  printf("usuwam\n");
  ma_delete(a[0]);
  ma_delete(a[1]);
  return PASS;
}

// Testuje reakcję implementacji na niepowodzenie alokacji pamięci.
// Błąd alokacji jest zgłaszany raz. Druga próba powinna się udać.
static unsigned long alloc_fail_test(void) {
  const uint64_t q1 = 1;
  unsigned long visited = 0;
  moore_t *maf, *mas;

  errno = 0;
  if ((maf = ma_create_full(64, 64, 64, t_one, y_one, &q1)) != NULL)
    visited |= V(1, 0);
  else if (errno == ENOMEM &&
           (maf = ma_create_full(64, 64, 64, t_one, y_one, &q1)) != NULL)
    visited |= V(2, 0);
  else
    return visited |= V(4, 0); // To nie powinno się wykonać.

  errno = 0;
  if ((mas = ma_create_simple(1, 1, t_two)) != NULL)
    visited |= V(1, 1);
  else if (errno == ENOMEM && (mas = ma_create_simple(1, 1, t_two)) != NULL)
    visited |= V(2, 1);
  else
    return visited |= V(4, 1); // To nie powinno się wykonać.

  ma_delete(maf);
  ma_delete(mas);

  return visited;
}

// Testuje reakcję implementacji na niepowodzenie alokacji pamięci.
static int memory_test(unsigned long (* test_function)(void)) {
  memory_test_data_t *mtd = get_memory_test_data();

  unsigned fail = 0, pass = 0;
  mtd->call_total = 0;
  mtd->fail_counter = 1;
  while (fail < 3 && pass < 3) {
    mtd->call_counter = 0;
    mtd->alloc_counter = 0;
    mtd->free_counter = 0;
    mtd->function_name = NULL;
    unsigned long visited_points = test_function();
    if (mtd->alloc_counter != mtd->free_counter ||
        (visited_points & 0444444444444444444444UL) != 0) {
      fprintf(stderr,
              "fail_counter %u, alloc_counter %u, free_counter %u, "
              "function_name %s, visited_point %lo\n",
              mtd->fail_counter, mtd->alloc_counter, mtd->free_counter,
              mtd->function_name, visited_points);
      ++fail;
    }
    if (mtd->function_name == NULL)
      ++pass;
    else
      pass = 0;
    mtd->fail_counter++;
  }

  return mtd->call_total > 0 && fail == 0 ? PASS : FAIL;
}

// Testuje reakcję implementacji na niepowodzenie alokacji pamięci.
static int memory(void) {
  memory_tests_check();
  return memory_test(alloc_fail_test);
}

// Dla s = 1, 96, funkcja ustawia nowy stan jako negację wejścia.
void transition_test2_f(uint64_t *next_state, uint64_t const *input,
	uint64_t const *state, size_t n, size_t s) {

    (void) n;
    (void) state;

	if (s == 1)
		next_state[0] = !input[0];
	else if (s == 96) {
		next_state[0] = ~input[0];
		next_state[1] = ~input[1] & 0x00000000ffffffff;
	}
}

void transition_add_f(uint64_t *next_state, uint64_t const *input,
	uint64_t const *state, size_t n, size_t s) {

	next_state[1] = state[1] + input[1];
}


// test 2 z dysku
static int test2(void) {

	moore_t *a1 = ma_create_simple(100, 100, &transition_add_f);
	ma_set_state(a1, (uint64_t [2]) {0, 1});
	uint64_t const *a1_out = ma_get_output(a1);
	ma_set_input(a1, (uint64_t [2]) {0, 0});

	// Argumenty poza zakresem, więc połączenie nie powinno się wykonać.
	ma_connect(a1, 64, a1, 64, 100);
	ma_step(&a1, 1);
	ASSERT(a1_out[1] == (uint64_t) 1);

	// Teraz już powinno się wykonać.
	ma_connect(a1, 64, a1, 64, 36);

	for (size_t i = 0; i < 5; i++)
		ma_step(&a1, 1);
	ASSERT(a1_out[1] == 32);

	const size_t a2_size = 8;
	moore_t *a2[a2_size];
	uint64_t const *a2_output[a2_size];

	for (size_t i = 0; i < a2_size; i++) {
		a2[i] = ma_create_simple(1, 1, &transition_test2_f);
		a2_output[i] = ma_get_output(a2[i]);
		ASSERT(a2_output[i][0] == 0);

		ma_set_input(a2[i], (uint64_t [1]) {1});
		ma_connect(a2[i], 0, a1, 0, 1);
		ma_step(&a2[i], 1);
		ASSERT(a2_output[i][0] == 1);
	}

	moore_t *a3 = ma_create_simple(96, 96, &transition_test2_f);
	ma_set_state(a3, (uint64_t [2]) {~(uint64_t) 0, 0x00000000ffffffff});
	uint64_t const *a3_output = ma_get_output(a3);
	ASSERT(a3_output[1] == 0x00000000ffffffff && a3_output[0] == ~(uint64_t) 0);

	for (size_t i = 0; i < 96; i++)
		ma_connect(a3, i, a2[i % 8], 0, 1);
	ma_step(&a3, 1);
	ASSERT(a3_output[1] == 0 && a3_output[0] == 0);

	ma_set_state(a1, (uint64_t [2]) {1, 0});
	ma_step(a2, a2_size);
	for (size_t i = 0; i < a2_size; i++) {
		ASSERT(a2_output[i][0] == 0);
	}

	for (size_t i = 0; i < a2_size; i++)
		ma_delete(a2[i]);
	ma_delete(a1);
	ma_delete(a3);

	return PASS;
}

// TEST TRZY
void t_times3(uint64_t *next_state, uint64_t const *input, uint64_t const *old_state, size_t, size_t) {
  next_state[0] = 3 * input[0];
}

void t_plus(uint64_t *next_state, uint64_t const *input, uint64_t const *old_state, size_t, size_t) {
  next_state[0] = old_state[0] + input[0];
}

void t_shift(uint64_t *next_state, uint64_t const *input, uint64_t const *old_state, size_t n, size_t s) {
  next_state[0] = input[0] >> 60;
  if (s > 64 && n > 64) next_state[1] = input[1];
}

void y_plus1(uint64_t *output, uint64_t const *state, size_t, size_t) {
  output[0] = state[0] + 1;
}

void y_times10(uint64_t *output, uint64_t const *state, size_t, size_t) {
  output[0] = state[0] *10;
}

static int mycustom(void) {
  moore_t *a;
  a = ma_create_simple(10, 10, t_shift);
  ma_delete(a);

  return PASS;
}

static int custom(void) {
  uint64_t x = 2;
  uint64_t x2 = 10;
  const uint64_t q1 = 0;
  const uint64_t *y[3];
  moore_t *a[3];
  const uint64_t zero[2] = {0, 0};

  a[0] = ma_create_full(10, 10, 10, t_times3, y_plus1, &q1);
  a[1] = ma_create_full(10, 10, 10, t_plus, y_times10, &q1);
  printf("tworze simple\n");
  a[2] = ma_create_simple(100, 100, t_shift);
  assert(a[0]);
  assert(a[1]);
  assert(a[2]);

  /*
  Stan automatów:
  0 -> 0 -> 1
  0 -> 0 -> 0
  0, 0 -> 0, 0 -> 0, 0
  */

  y[0] = ma_get_output(a[0]);
  y[1] = ma_get_output(a[1]);
  y[2] = ma_get_output(a[2]);

  ASSERT(y[0] != NULL);
  printf("%d\n", y[0][0]);
  ASSERT(y[0][0] == 1);
  ASSERT(y[1] != NULL);
  printf("%d\n", y[1][0]);
  ASSERT(y[1][0] == 0);
  ASSERT(y[2] != NULL);
  printf("%d %d\n", y[2][0], y[2][1]);
  ASSERT(y[2][0] == 0 && y[2][1] == 0);

  //Przepisujemy bity z wyjscia a[0] na wyjście a[1]
  ASSERT(ma_connect(a[1], 0, a[0], 0, 10) == 0);
  //Przepisujemy bity z wyjścia a[1] na bity 60-69 wejścia a[1]
  //tym samym rodzielamy wyjście a[1] na 2 części 4-bitową i 6-bitową
  ASSERT(ma_connect(a[2], 60, a[1], 0, 10) == 0);

  printf("connecty dzialaja\n");

  ma_set_input(a[0], &x);
  ma_set_input(a[1], zero);
  ma_set_input(a[2], zero);

  ma_step(a, 1);
  ma_step(&(a[1]), 1);
  ma_step(&(a[2]), 1);


  /*
  Stan automatów:
  2 -> 6 -> 7
  7 -> 7 -> 70
  2^61 + 2^62, 4 -> 6, 4 -> 6, 4
  */

  ASSERT(y[0][0] == 7);
  ASSERT(y[1][0] == 70);
  ASSERT(y[2][0] == 6);
  ASSERT(y[2][1] == 4);

  printf("%d\n", y[0][0]);
  printf("%d\n", y[1][0]);
  printf("%d\n", y[2][0]);
  printf("%d\n", y[2][1]);

  //odłączamy pierwszy bit wejścia automatu 1
  ma_disconnect(a[1], 0, 1);
  //zastępujemy go zeraem (podłaczone bity pozostają nietknięte)
  //teraz na wejściu a[1] powinno znajdowac się 6
  ma_set_input(a[1], &q1);
  ma_step(&(a[1]), 1);
  ASSERT(y[1][0] == 130);


  /*
  Stan automatów:
  2 -> 6 -> 7
  6 -> 13 -> 130
  2^61, 8 -> 6, 4 -> 6, 4
  */

  ASSERT(y[0][0] == 7);
  ASSERT(y[1][0] == 130);
  ASSERT(y[2][0] == 6);
  ASSERT(y[2][1] == 4);

  printf("%d\n", y[0][0]);
  printf("%d\n", y[1][0]);
  printf("%d\n", y[2][0]);
  printf("%d\n", y[2][1]);

  ma_set_input(a[0], &x2);
  ma_step(a, 3);

  ASSERT(y[0][0] == 31);
  ASSERT(y[1][0] == 190);
  ASSERT(y[2][0] == 2);
  ASSERT(y[2][1] == 8);

  printf("%d\n", y[0][0]);
  printf("%d\n", y[1][0]);
  printf("%d\n", y[2][0]);
  printf("%d\n", y[2][1]);

  /*
  Stan automatów:
  10 -> 30 -> 31
  (nieistotne (31)) -> 19 -> 190
  (niestotne) -> 2, 8 -> 2, 8
  */


  ma_delete(a[0]);
  printf("delete dziala1\n");
  ma_delete(a[1]);
  printf("delete dziala2\n");
  ma_delete(a[2]);
  printf("delete dziala3\n");

  return PASS;
}

// test counter

uint64_t popcount64(uint64_t x) {
  uint64_t count = 0;
  while (x) {
      count += x & 1;
      x >>= 1;
  }
  return count;
}

void t_zero(uint64_t *next_state, uint64_t const *input, uint64_t const *old_state, size_t n, size_t s) {
    for (size_t i = 0; i <= s/64; i++) next_state[i] = 0;
  }

  void t_bitcounter(uint64_t *next_state, uint64_t const *input, uint64_t const *old_state, size_t n, size_t s) {
    next_state[0] = 0;
    for (size_t i = 0; i <= n/64; i++) next_state[0] += popcount64(input[i]);
  }

  const uint64_t STATE_MOD = 6765878346298313;
  void refresh_state(uint64_t state[]) {
    state[0] = (state[0] + 2*state[1])%STATE_MOD;
    state[1] = (3*state[0] + state[1])%STATE_MOD;
  }

  /*
    Test tworzy N + 1 automatów simple
    Automaty w tablicy a - mają 0 wejścia i funkcję tranzycji zerująca stan
    Automat counter zlicza bity na wejściu - ma on duuuże wejście, do którego podpinają się automaty a (do niezależnych fragmentów)
    Następnie automaty z tablicy a po kolei zerują swoje wejście (wykonując krok)
  */
  static int counter_test(void) {
    const size_t N = 30;
    const size_t p = 131;
    const size_t c = 257;
    moore_t* a[N];
    for (size_t i = 0; i < N; i++) {
      a[i] = ma_create_simple(0, 124, t_zero);
      assert(a[i]);
    }
    moore_t* counter = ma_create_simple(5000, 30, t_bitcounter);
    const uint64_t *y = ma_get_output(counter);
    assert(counter);
    assert(y);
    ASSERT(y[0] == 0);

    uint64_t state[2];
    state[0] = 89327592387342423;
    state[1] = 90780953242323231;
    size_t perm[N];
    //w miarę losowa permutacja liczb 0, ..., N-1
    perm[0] = 7; for (size_t i = 1; i < N; i++) perm[i] = (perm[i-1] + 11)%N;

    uint64_t expected_ans = 0;
    for (size_t perm_id = 0; perm_id < N; perm_id++) {
      //generujemy losowy stan a[i] i podpinamy jego wyjście (121 bitów) do przedziału wejścia countera
      size_t i = perm[perm_id];
      refresh_state(state);
      ma_set_state(a[i], state);
      ma_connect(counter, (i*p) + c, a[i], 0, 121);
      ma_step(&counter, 1);
      expected_ans += popcount64(state[0]) + popcount64(state[1]);
      ASSERT(y[0] == expected_ans);
    }

    //printf("\n \nReshuffling \n \n");
    //w miarę losowa permutacja liczb 0, ..., N-1
    perm[0] = 13; for (size_t i = 1; i < N; i++) perm[i] = (perm[i-1] + 17)%N;

    for (size_t perm_id = 0; perm_id < N; perm_id++) {
      size_t i = perm[perm_id];

      //czyscimy (step dla a[i] oznacza wyzerowanie outputu)
      uint64_t* curr_y = ma_get_output(a[i]);
      assert(curr_y);
      expected_ans -= popcount64(curr_y[0]) + popcount64(curr_y[1]);
      ma_step(&(a[i]), 1);

      ma_step(&counter, 1);
      ASSERT(y[0] == expected_ans);
    }


    for (size_t i = 0; i < N; i++) ma_delete(a[i]);
    ma_delete(counter);
    printf("PASS\n");
    return PASS;
  }


/** URUCHAMIANIE TESTÓW **/

typedef struct {
  char const *name;
  int (*function)(void);
} test_list_t;

#define TEST(t) {#t, t}

static const test_list_t test_list[] = {
  TEST(one),
  TEST(two),
  TEST(memory),
	TEST(test2),
  TEST(custom),
  TEST(mycustom),
  TEST(counter_test),
};

static int do_test(int (*function)(void)) {
  int result = function();
  puts("quite long magic string");
  return result;
}

int main(int argc, char *argv[]) {
  if (argc == 2)
    for (size_t i = 0; i < SIZE(test_list); ++i)
      if (strcmp(argv[1], test_list[i].name) == 0)
        return do_test(test_list[i].function);

  fprintf(stderr, "Użycie:\n%s nazwa_testu\n", argv[0]);
  return WRONG_TEST;
}
