#ifdef NDEBUG
#undef NDEBUG
#endif

#include "ma.h"
#include "memory_tests.h"
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/** MAKRA SKRACAJĄCE IMPLEMENTACJĘ TESTÓW **/

// To są możliwe wyniki testu.
#define PASS 0
#define FAIL 1
#define WRONG_TEST 2

// Oblicza liczbę elementów tablicy x.
#define SIZE(x) (sizeof x / sizeof x[0])

#define ASSERT(f)                                 \
  do {                                            \
    if (!(f))                                     \
      return FAIL;                                \
  } while (0)

#define CHECK(b, v, w)                            \
  do {                                            \
    if (((v) & (UINT64_MAX >> (64 - b))) != (w))  \
      return FAIL;                                \
  } while (0)

#define TEST_EINVAL(f)                            \
  do {                                            \
    errno = 0;                                    \
    if ((f) != -1 || errno != EINVAL)             \
      return FAIL;                                \
  } while (0)

#define TEST_NULL_EINVAL(f)                       \
  do {                                            \
    errno = 0;                                    \
    if ((f) != NULL || errno != EINVAL)           \
      return FAIL;                                \
  } while (0)

#define TEST_ENOMEM(f)                            \
  do {                                            \
    errno = 0;                                    \
    if ((f) != NULL || errno != ENOMEM)           \
      return FAIL;                                \
  } while (0)

#define V(code, where) (((unsigned long)code) << (3 * where))

/** WŁAŚCIWE TESTY **/

static void t_one(uint64_t *next_state, uint64_t const *input,
                  uint64_t const *old_state, size_t, size_t) {
  next_state[0] = old_state[0] + input[0];
}

static void y_one(uint64_t *output, uint64_t const *state, size_t, size_t) {
  output[0] = state[0] + 1;
}

static void t_two(uint64_t *next_state, uint64_t const *input,
                  uint64_t const *old_state, size_t, size_t) {
  next_state[0] = old_state[0] ^ input[0];
}

static void t_four(uint64_t *next_state, uint64_t const *,
                   uint64_t const *old_state, size_t, size_t) {
  next_state[0] = (old_state[0] & 15) ^ 6;
}

static void t_three(uint64_t *next_state, uint64_t const *input,
                    uint64_t const *old_state, size_t, size_t) {
  next_state[0] = (((old_state[0] & 511) + 3) * (input[0] & 7)) & 511;
}

static void t_eight(uint64_t *next_state, uint64_t const *input,
                    uint64_t const *old_state, size_t, size_t) {
  next_state[0] = (((old_state[0] & 511) + 8) * (input[0] & 255)) & 511;
}

static void t_neg(uint64_t *next_state, uint64_t const *,
                  uint64_t const *old_state, size_t, size_t) {
  next_state[0] = (old_state[0] & 1) ^ 1;
}

static void t_const(uint64_t *next_state, uint64_t const *,
                    uint64_t const *old_state, size_t, size_t s) {
  s = (s + 63)/64;
  for (size_t i = 0; i < s; ++i)
    next_state[i] = old_state[i];
}

static void t_forward(uint64_t *next_state, uint64_t const *input,
                      uint64_t const *, size_t n, size_t s) {
  n = (n + 63)/64;
  s = (s + 63)/64;
  size_t i = 0;
  for (; i < n && i < s; ++i)
    next_state[i] = input[i];
  for (; i < s; ++i)
    next_state[i] = 0;
}

static void y_forward(uint64_t *output, uint64_t const *state,
                      size_t m, size_t s) {
  m = (m + 63)/64;
  s = (s + 63)/64;
  size_t i = 0;
  for (; i < m && i < s; ++i)
    output[i] = state[i];
  for (; i < m; ++i)
    output[i] = 0;
}

static void t_poly(uint64_t *next_state, uint64_t const *input,
                   uint64_t const *, size_t, size_t) {
  // input[0] – wartość wielomianu
  // input[1] – wartość argumentu
  // input[2] – współczynnik wielomianu
  // state[0] – wartość wielomianu
  // state[1] – wartość argumentu
  next_state[0] = input[0] * input[1] + input[2];
  next_state[1] = input[1];
}

static void t_shift(uint64_t *next_state, uint64_t const *input,
                    uint64_t const *state, size_t n, size_t s) {
  next_state[0] = state[0] << n | (input[0] & (UINT64_MAX >> (64 - n)));
  next_state[0] &= UINT64_MAX >> (64 - s);
}

static void y_shift(uint64_t *output, uint64_t const *state,
                    size_t m, size_t s) {
  output[0] = state[0] ^ (UINT64_MAX >> (64 - s));
  if (m > s)
    output[0] <<= m - s;
  else if (m < s)
    output[0] >>= s - m;
}

// Testuje jeden automat wykonujący jakieś dodawania.
static int one(void) {
  const uint64_t q1 = 1, x3 = 3, *y;

  moore_t *a = ma_create_full(64, 64, 64, t_one, y_one, &q1);
  assert(a);

  y = ma_get_output(a);
  ASSERT(y != NULL);
  ASSERT(ma_set_input(a, &x3) == 0);
  ASSERT(y[0] == 2);
  ASSERT(ma_step(&a, 1) == 0);
  ASSERT(y[0] == 5);
  ASSERT(ma_step(&a, 1) == 0);
  ASSERT(y[0] == 8);
  ASSERT(ma_set_input(a, &q1) == 0);
  ASSERT(ma_set_state(a, &x3) == 0);
  ASSERT(y[0] == 4);
  ASSERT(ma_step(&a, 1) == 0);
  ASSERT(y[0] == 5);
  ASSERT(ma_step(&a, 1) == 0);
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

  y[0] = ma_get_output(a[0]);
  y[1] = ma_get_output(a[1]);
  ASSERT(y[0] != NULL);
  ASSERT(y[1] != NULL);

  // Na początku licznik ma wartość 00.
  ASSERT(ma_set_input(a[0], &x) == 0);
  ASSERT(ma_connect(a[1], 0, a[0], 0, 1) == 0);
  ASSERT(y[1][0] == 0 && y[0][0] == 0);

  // Po jednym kroku licznik ma wartość 01.
  ASSERT(ma_step(a, 2) == 0);
  ASSERT(y[1][0] == 0 && y[0][0] == 1);

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

  // Po rozłączeniu automatów starszy bit licznika przestaje się zmieniać.
  ASSERT(ma_disconnect(a[1], 0, 1) == 0);
  x = 0;
  ASSERT(ma_set_input(a[1], &x) == 0);
  ASSERT(ma_step(a, 2) == 0);
  ASSERT(y[1][0] == 0 && y[0][0] == 0);
  ASSERT(ma_step(a, 2) == 0);
  ASSERT(y[1][0] == 0 && y[0][0] == 1);

  ma_delete(a[0]);
  ma_delete(a[1]);
  return PASS;
}

// Testuje łączenie i rozłączanie automatów.
static int connections(void) {
  uint64_t x = 0;
  const uint64_t *y;
  moore_t *a[5];

  a[0] = ma_create_simple(32, 32, t_forward);
  assert(a[0]);
  for (uint64_t i = 1; i <= 4; ++i) {
    a[i] = ma_create_simple(0, 4, t_const);
    assert(a[i]);
    ASSERT(ma_set_state(a[i], &i) == 0);
    ASSERT(ma_connect(a[0], 4 * i, a[i], 0, 4) == 0);
  }
  y = ma_get_output(a[0]);
  CHECK(32, y[0], 0);
  ASSERT(ma_set_input(a[0], &x) == 0);
  ASSERT(ma_step(a, 1) == 0);
  CHECK(32, y[0], 0x43210);
  ASSERT(ma_connect(a[0], 17, a[4], 1, 2) == 0);
  ASSERT(ma_connect(a[0], 20, a[1], 0, 4) == 0);
  ASSERT(ma_connect(a[0], 12, a[1], 0, 4) == 0);
  ASSERT(ma_disconnect(a[0], 1, 2) == 0);
  ASSERT(ma_set_input(a[0], &x) == 0);
  ASSERT(ma_step(a, 1) == 0);
  CHECK(32, y[0], 0x141210);
  x = 0x8a7b6c5d;
  ASSERT(ma_set_input(a[0], &x) == 0);
  ASSERT(ma_step(a, 1) == 0);
  CHECK(32, y[0], 0x8a14121d);
  ma_delete(a[1]);
  a[1] = NULL;
  ASSERT(ma_set_input(a[0], &x) == 0);
  ASSERT(ma_step(a, 1) == 0);
  CHECK(32, y[0], 0x8a74625d);
  ASSERT(ma_disconnect(a[0], 8, 4) == 0);
  ASSERT(ma_set_input(a[0], &x) == 0);
  ASSERT(ma_step(a, 1) == 0);
  CHECK(32, y[0], 0x8a746c5d);
  ASSERT(ma_connect(a[0], 24, a[0], 0, 4) == 0);
  ASSERT(ma_set_input(a[0], &x) == 0);
  ASSERT(ma_step(a, 1) == 0);
  CHECK(32, y[0], 0x8d746c5d);

  for (uint64_t i = 0; i < 5; ++i)
    ma_delete(a[i]);
  return PASS;
}

// Testuje stan nieustalony na wejściach automatów.
static int undetermined(void) {
  const uint64_t s = 3, *y[2];
  uint64_t x;
  moore_t *a[2];

  a[0] = ma_create_simple(4, 4, t_four);
  a[1] = ma_create_simple(4, 4, t_four);
  assert(a[0]);
  assert(a[1]);

  ASSERT(ma_connect(a[1], 0, a[0], 0, 4) == 0);
  ASSERT(ma_set_state(a[1], &s) == 0);
  y[0] = ma_get_output(a[0]);
  y[1] = ma_get_output(a[1]);
  ASSERT(y[0] != NULL && y[1] != NULL);
  CHECK(4, y[0][0], 0);
  CHECK(4, y[1][0], 3);
  ASSERT(ma_step(a, 2) == 0);
  CHECK(4, y[0][0], 6);
  CHECK(4, y[1][0], 5);
  ASSERT(ma_disconnect(a[1], 0, 4) == 0);
  ASSERT(ma_step(a, 2) == 0);
  CHECK(4, y[0][0], 0);
  CHECK(4, y[1][0], 3);
  x = 15;
  ASSERT(ma_set_input(a[1], &x) == 0);
  CHECK(4, y[1][0], 3);
  x = 10;
  ASSERT(ma_set_input(a[1], &x) == 0);
  CHECK(4, y[1][0], 3);

  ma_delete(a[0]);
  ma_delete(a[1]);
  return PASS;
}

// Testuje kasowanie automatu i utworzenie w jego miejsce nowego.
static int delete(void) {
  moore_t *a[5];
  const uint64_t *y[SIZE(a)];
  uint64_t q = 1, x = 2;

  a[0] = ma_create_full(8, 8, 9, t_eight, y_forward, &q);
  for (size_t i = 1; ++q, i < SIZE(a); ++i)
    assert((a[i] = ma_create_full(3, 3, 9, t_three, y_forward, &q)));

  for (size_t i = 0; i < SIZE(a); ++i)
    assert((y[i] = ma_get_output(a[i])));

  for (size_t i = 1; i <= 2; ++i, ++x)
    ASSERT(ma_set_input(a[i], &x) == 0);

  CHECK(8, y[0][0], 1);
  CHECK(3, y[1][0], 2);
  CHECK(3, y[2][0], 3);
  CHECK(3, y[3][0], 4);
  CHECK(3, y[4][0], 5);

  ASSERT(ma_connect(a[0], 0, a[0], 6, 2) == 0);
  ASSERT(ma_connect(a[0], 2, a[1], 0, 3) == 0);
  ASSERT(ma_connect(a[0], 5, a[2], 0, 3) == 0);
  ASSERT(ma_connect(a[3], 0, a[0], 0, 3) == 0);
  ASSERT(ma_connect(a[4], 0, a[0], 3, 3) == 0);

  ASSERT(ma_step(a, SIZE(a)) == 0);
  ASSERT(ma_step(a, SIZE(a)) == 0);

  CHECK(8, y[0][0], 224);
  CHECK(3, y[1][0], 2);
  CHECK(3, y[2][0], 7);
  CHECK(3, y[3][0], 0);
  CHECK(3, y[4][0], 7);

  ma_delete(a[0]);
  assert((a[0] = ma_create_full(8, 8, 9, t_eight, y_forward, &q)));
  assert((y[0] = ma_get_output(a[0])));

  CHECK(8, y[0][0], 6);
  CHECK(3, y[1][0], 2);
  CHECK(3, y[2][0], 7);
  CHECK(3, y[3][0], 0);
  CHECK(3, y[4][0], 7);

  ASSERT(ma_connect(a[0], 6, a[0], 0, 2) == 0);
  ASSERT(ma_connect(a[0], 0, a[1], 0, 3) == 0);
  ASSERT(ma_connect(a[0], 3, a[2], 0, 3) == 0);
  ASSERT(ma_connect(a[3], 0, a[0], 2, 3) == 0);
  ASSERT(ma_connect(a[4], 0, a[0], 5, 3) == 0);

  ASSERT(ma_step(a, SIZE(a)) == 0);
  ASSERT(ma_step(a, SIZE(a)) == 0);

  CHECK(8, y[0][0], 40);
  CHECK(3, y[1][0], 2);
  CHECK(3, y[2][0], 3);
  CHECK(3, y[3][0], 2);
  CHECK(3, y[4][0], 3);

  for (size_t i = 0; i < SIZE(a); ++i)
    ma_delete(a[i]);
  return PASS;
}

// Testuje sprawdzanie poprawności argumentów.
static int params(void) {
  const uint64_t q = 0;

  TEST_NULL_EINVAL(ma_create_full(1, 0, 1, t_const, y_forward, &q));
  TEST_NULL_EINVAL(ma_create_full(1, 1, 0, t_const, y_forward, &q));
  TEST_NULL_EINVAL(ma_create_full(1, 1, 1, NULL, y_forward, &q));
  TEST_NULL_EINVAL(ma_create_full(1, 1, 1, t_const, NULL, &q));
  TEST_NULL_EINVAL(ma_create_full(1, 1, 1, t_const, y_forward, NULL));
  TEST_NULL_EINVAL(ma_create_simple(1, 0, t_const));
  TEST_NULL_EINVAL(ma_create_simple(1, 1, NULL));

  moore_t *a[3];
  a[0] = ma_create_full(0, 1, 1, t_neg, y_forward, &q);
  a[1] = ma_create_full(1, 2, 3, t_neg, y_forward, &q);
  a[2] = NULL;
  assert(a[0]);
  assert(a[1]);

  TEST_EINVAL(ma_connect(NULL, 0, a[0], 0, 1));
  TEST_EINVAL(ma_connect(a[1], 0, NULL, 0, 1));
  TEST_EINVAL(ma_connect(a[1], 0, a[0], 0, 0));
  TEST_EINVAL(ma_connect(a[1], 1, a[0], 0, 1));
  TEST_EINVAL(ma_connect(a[1], 0, a[0], 1, 1));
  TEST_EINVAL(ma_connect(a[1], 0, a[0], 0, 2));

  TEST_EINVAL(ma_disconnect(NULL, 0, 1));
  TEST_EINVAL(ma_disconnect(a[0], 0, 1));
  TEST_EINVAL(ma_disconnect(a[1], 0, 0));
  TEST_EINVAL(ma_disconnect(a[1], 0, 2));
  TEST_EINVAL(ma_disconnect(a[1], 1, 1));

  TEST_EINVAL(ma_set_input(NULL, &q));
  TEST_EINVAL(ma_set_input(a[1], NULL));
  TEST_EINVAL(ma_set_input(a[0], &q));

  TEST_EINVAL(ma_set_state(NULL, &q));
  TEST_EINVAL(ma_set_state(a[1], NULL));

  TEST_NULL_EINVAL(ma_get_output(NULL));

  TEST_EINVAL(ma_step(NULL, 1));
  CHECK(1, ma_get_output(a[0])[0], 0);
  CHECK(2, ma_get_output(a[1])[0], 0);
  TEST_EINVAL(ma_step(a, 3));
  CHECK(1, ma_get_output(a[0])[0], 0);
  CHECK(2, ma_get_output(a[1])[0], 0);
  TEST_EINVAL(ma_step(a, 0));
  CHECK(1, ma_get_output(a[0])[0], 0);
  CHECK(2, ma_get_output(a[1])[0], 0);
  ASSERT(ma_step(a, 2) == 0);
  CHECK(1, ma_get_output(a[0])[0], 1);
  CHECK(2, ma_get_output(a[1])[0], 1);

  ma_delete(a[0]);
  ma_delete(a[1]);
  ma_delete(a[2]);
  return PASS;
}

// Testuje złośliwe przypadki.
static int malicious(void) {
  moore_t *a0 = ma_create_simple(3, 3, t_const);
  moore_t *a1 = ma_create_simple(3, 3, t_const);

  TEST_EINVAL(ma_connect(a0, 1, a1, 1, SIZE_MAX));
  TEST_EINVAL(ma_connect(a0, SIZE_MAX, a1, 1, 1));
  TEST_EINVAL(ma_connect(a0, 1, a1, SIZE_MAX, 1));

  TEST_EINVAL(ma_disconnect(a0, 1, SIZE_MAX));
  TEST_EINVAL(ma_disconnect(a0, SIZE_MAX, 1));

  ma_delete(a0);
  ma_delete(a1);
  return PASS;
}

// Testuje potokowe obliczanie wielomianu.
static int pipeline(void) {
  moore_t *a[3];
  uint64_t x[3 * SIZE(a)] = {0, 0, 1, 0, 0, 2, 0, 0, 3}; // wielomian x^2 + 2x + 3
  const uint64_t y[] = {3, 6, 11, 18, 27}; // wartości wielomianu dla x = 0, 1, …, 4

  for (size_t i = 0; i < SIZE(a); ++i) {
    a[i] = ma_create_simple(192, 128, t_poly);
    assert(a[i]);
  }
  ASSERT(ma_set_input(a[0], &x[0]) == 0);
  for (size_t i = 1; i < SIZE(a); ++i) {
    ASSERT(ma_connect(a[i], 0, a[i - 1], 0, 128) == 0);
    ASSERT(ma_set_input(a[i], &x[3 * i]) == 0);
  }
  for (size_t i = 0; i < SIZE(y); ++i) {
    x[1] = i;
    ASSERT(ma_set_input(a[0], x) == 0);
    ASSERT(ma_step(a, SIZE(a)) == 0);
    if (i >= SIZE(a) - 1)
      ASSERT(ma_get_output(a[SIZE(a) - 1])[0] == y[i - SIZE(a) + 1]);
  }
  for (size_t i = SIZE(y) - SIZE(a) + 1; i < SIZE(y); ++i) {
    ASSERT(ma_step(a, SIZE(a)) == 0);
    ASSERT(ma_get_output(a[SIZE(a) - 1])[0] == y[i]);
  }

  for (size_t i = 0; i < SIZE(a); ++i)
    ma_delete(a[i]);
  return PASS;
}

// Testuje zmiany stanu.
static int shift(void) {
  static const uint64_t y[40][2] = {
    {0xffffffffffff, 0xffffffffffff00},
    {0xffffffffffff, 0xfffffffffffe00},
    {0xffffffffffff, 0xffffffffffbd00},
    {0xfffffffffffb, 0xffffffffef7c00},
    {0xffffffffff77, 0xfffffffbdf3b00},
    {0xffffffffeef3, 0xfffffef7cefa00},
    {0xfffffffdde6f, 0xffffbdf3beb900},
    {0xffffffbbcdeb, 0xffef7cefae7800},
    {0xfffff779bd67, 0xfbdf3beb9e3700},
    {0xfffeef37ace2, 0xf7cefae78df600},
    {0xffdde6f59c5e, 0xf3beb9e37db500},
    {0xfbbcdeb38bda, 0xefae78df6d7400},
    {0x779bd6717b56, 0xeb9e37db5d3300},
    {0xf37ace2f6ad2, 0xe78df6d74cf200},
    {0x6f59c5ed5a4e, 0xe37db5d33cb100},
    {0xeb38bdab49ca, 0xdf6d74cf2c7000},
    {0xfffffffffffd, 0xfffffffffbef00},
    {0xffffffffffbd, 0xfffffffefbee00},
    {0xfffffffff7bd, 0xffffffbefbad00},
    {0xfffffffef7b9, 0xffffefbeeb6c00},
    {0xffffffdef735, 0xfffbefbadb2b00},
    {0xfffffbdee6b1, 0xfefbeeb6caea00},
    {0xffff7bdcd62d, 0xbefbadb2baa900},
    {0xffef7b9ac5a9, 0xbeeb6caeaa6800},
    {0xfdef7358b525, 0xbadb2baa9a2700},
    {0xbdee6b16a4a0, 0xb6caeaa689e600},
    {0xbdcd62d4941c, 0xb2baa9a279a500},
    {0xb9ac5a928398, 0xaeaa689e696400},
    {0x358b52507314, 0xaa9a279a592300},
    {0xb16a4a0e6290, 0xa689e69648e200},
    {0x2d4941cc520c, 0xa279a59238a100},
    {0xa928398a4188, 0x9e69648e286000},
    {0xfffffffffffb, 0xfffffffff7df00},
    {0xffffffffff7f, 0xfffffffdf7de00},
    {0xffffffffefff, 0xffffff7df79d00},
    {0xfffffffdfffb, 0xffffdf7de75c00},
    {0xffffffbfff77, 0xfff7df79d71b00},
    {0xfffff7ffeef3, 0xfdf7de75c6da00},
    {0xfffefffdde6f, 0x7df79d71b69900},
    {0xffdfffbbcdeb, 0x7de75c6da65800},
  };
  const uint64_t q = 0;

  moore_t *a[2];
  a[0] = ma_create_full(5, 48, 56, t_shift, y_shift, &q);
  a[1] = ma_create_full(6, 56, 48, t_shift, y_shift, &q);
  assert(a[0]);
  assert(a[1]);

  for (size_t i = 0; i < SIZE(y); ++i) {
    if ((i & 0xf) == 0) {
      ASSERT(ma_set_state(a[0], &i) == 0);
      ASSERT(ma_set_state(a[1], &i) == 0);
    }
    ASSERT(ma_set_input(a[0], &i) == 0);
    ASSERT(ma_set_input(a[1], &i) == 0);
    ASSERT(ma_step(a, 2) == 0);
    CHECK(48, ma_get_output(a[0])[0], y[i][0]);
    CHECK(56, ma_get_output(a[1])[0], y[i][1]);
  }

  ma_delete(a[0]);
  ma_delete(a[1]);
  return PASS;
}

// Testuje wiele automatów połączonych w cykl.
static int cycle(void) {
  const uint64_t q = 0;
  moore_t *a[800];

  for (size_t i = 0; i < SIZE(a); ++i) {
    a[i] = ma_create_full(64, 64, 64, t_forward, y_one, &q);
    assert(a[i]);
  }

  for (size_t i = 0; i < SIZE(a) - 1; ++i)
    ASSERT(ma_connect(a[i + 1], 0, a[i], 0, 64) == 0);
  ASSERT(ma_connect(a[0], 0, a[SIZE(a) - 1], 0, 64) == 0);

  for (uint64_t i = 0; i < 2 * SIZE(a); ++i) {
    ASSERT(ma_get_output(a[0])[0] == i + 1);
    ASSERT(ma_step(a, SIZE(a)) == 0);
  }
  ASSERT(ma_get_output(a[0])[0] == 2 * SIZE(a) + 1);

  for (size_t i = 0; i < SIZE(a); ++i)
    ma_delete(a[i]);

  return PASS;
}

// Testuje próbę alokowania dużo za dużej pamięci.
static int alloc(void) {
  const uint64_t q = 0;

  TEST_ENOMEM(ma_create_full(SIZE_MAX, 1, 1, t_forward, y_forward, &q));
  TEST_ENOMEM(ma_create_full(1, SIZE_MAX, 1, t_forward, y_forward, &q));
  TEST_ENOMEM(ma_create_full(1, 1, SIZE_MAX, t_forward, y_forward, &q));
  TEST_ENOMEM(ma_create_simple(SIZE_MAX, 1, t_forward));
  TEST_ENOMEM(ma_create_simple(1, SIZE_MAX, t_forward));

  for (size_t i = 1; i <= 4; ++i) {
    const size_t big = (size_t)1 << (sizeof (size_t) * 8 - i);
    TEST_ENOMEM(ma_create_full(big, 1, 1, t_forward, y_forward, &q));
    TEST_ENOMEM(ma_create_full(1, big, 1, t_forward, y_forward, &q));
    TEST_ENOMEM(ma_create_full(1, 1, big, t_forward, y_forward, &q));
    TEST_ENOMEM(ma_create_simple(big, 1, t_forward));
    TEST_ENOMEM(ma_create_simple(1, big, t_forward));
  }

  return PASS;
}

// Testuje reakcję implementacji na niepowodzenie alokacji pamięci.
// Błąd alokacji jest zgłaszany raz. Druga próba powinna się udać.
// To jest przykładowy test udostępniony studentom.
static unsigned long alloc_fail_test_example(void) {
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
// Błąd alokacji jest zgłaszany raz. Druga próba powinna się udać.
// To jest zaawansowany test.
static unsigned long alloc_fail_test_advanced(void) {
  const uint64_t x = UINT64_MAX, y = 1, z = 7, *out;
  unsigned long visited = 0;
  moore_t *a[3];
  int res;

  errno = 0;
  if ((a[0] = ma_create_full(64, 64, 64, t_one, y_one, &y)) != NULL)
    visited |= V(1, 0);
  else if (errno == ENOMEM &&
           (a[0] = ma_create_full(64, 64, 64, t_one, y_one, &y)) != NULL)
    visited |= V(2, 0);
  else
    return visited |= V(4, 0); // To nie powinno się wykonać.

  errno = 0;
  if ((a[1] = ma_create_simple(192, 192, t_forward)) != NULL)
    visited |= V(1, 1);
  else if (errno == ENOMEM &&
           (a[1] = ma_create_simple(192, 192, t_forward)) != NULL)
    visited |= V(2, 1);
  else
    return visited |= V(4, 1); // To nie powinno się wykonać.

  errno = 0;
  if ((a[2] = ma_create_simple(64, 64, t_two)) != NULL)
    visited |= V(1, 2);
  else if (errno == ENOMEM &&
           (a[2] = ma_create_simple(64, 64, t_two)) != NULL)
    visited |= V(2, 2);
  else
    return visited |= V(4, 2); // To nie powinno się wykonać.

  errno = 0;
  if ((res = ma_connect(a[1], 32, a[2], 32, 32)) == 0)
    visited |= V(1, 3);
  else if (errno == ENOMEM && (res = ma_connect(a[1], 32, a[2], 32, 32)) == 0)
    visited |= V(2, 3);
  else
    return visited |= V(4, 3); // To nie powinno się wykonać.

  errno = 0;
  if ((res = ma_connect(a[1], 0, a[0], 0, 64)) == 0)
    visited |= V(1, 4);
  else if (errno == ENOMEM && (res = ma_connect(a[1], 0, a[0], 0, 64)) == 0)
    visited |= V(2, 4);
  else
    return visited |= V(4, 4); // To nie powinno się wykonać.

  errno = 0;
  if ((res = ma_connect(a[1], 0, a[0], 0, 8)) == 0)
    visited |= V(1, 5);
  else if (errno == ENOMEM && (res = ma_connect(a[1], 0, a[0], 0, 8)) == 0)
    visited |= V(2, 5);
  else
    return visited |= V(4, 5); // To nie powinno się wykonać.

  for (size_t i = 64; i < 192; ++i) {
    errno = 0;
    if ((res = ma_connect(a[1], i, a[2], 0, 1)) == 0)
      visited |= V(1, 6);
    else if (errno == ENOMEM && (res = ma_connect(a[1], i, a[2], 0, 1)) == 0)
      visited |= V(2, 6);
    else
      return visited |= V(4, 6); // To nie powinno się wykonać.
  }

  assert(ma_set_input(a[0], &z) == 0);
  assert(ma_set_input(a[2], &x) == 0);

  assert((out = ma_get_output(a[1])));
  assert(out[0] == 0 && out[1] == 0 && out[2] == 0);

  errno = 0;
  if (ma_step(a, SIZE(a)) == 0)
    visited |= V(1, 7);
  else if (errno == ENOMEM && ma_step(a, SIZE(a)) == 0)
    visited |= V(2, 7);
  else
    return visited |= V(4, 7); // To nie powinno się wykonać.

  assert(out[0] == 2 && out[1] == 0 && out[2] == 0);

  errno = 0;
  if (ma_step(a, SIZE(a)) == 0)
    visited |= V(1, 8);
  else if (errno == ENOMEM && ma_step(a, SIZE(a)) == 0)
    visited |= V(2, 8);
  else
    return visited |= V(4, 8); // To nie powinno się wykonać.

  assert(out[0] == 9 && out[1] == UINT64_MAX && out[2] == UINT64_MAX);

  errno = 0;
  if (ma_step(a, SIZE(a)) == 0)
    visited |= V(1, 9);
  else if (errno == ENOMEM && ma_step(a, SIZE(a)) == 0)
    visited |= V(2, 9);
  else
    return visited |= V(4, 9); // To nie powinno się wykonać.

  assert(out[0] == 16 && out[1] == 0 && out[2] == 0);

  for (size_t i = 0; i < SIZE(a); ++i)
    ma_delete(a[i]);

  return visited;
}

// Testuje reakcję implementacji na niepowodzenie alokacji pamięci.
// Błąd alokacji jest zgłaszany raz. Druga próba powinna się udać.
// Testuje rozłączanie automatów.
static unsigned long alloc_fail_test_disconnect(void) {
  const uint64_t q0[2] = {0x1111111111111111, 0x8888888888888888},
                 q1[2] = {0x9999999999999999, 0x6666666666666666},
                 x0[2] = {0x5555555555555555, 0xaaaaaaaaaaaaaaaa},
                 x1[2] = {0xc000000000000000, 0x0000000000000003},
                 y0[2] = {0xd555555555555555, 0xaaaaaaaaaaaaaaab}, *y1;
  unsigned long visited = 0;
  moore_t *a[2];

  errno = 0;
  if ((a[0] = ma_create_full(128, 128, 128, t_forward, y_forward, q0)) != NULL)
    visited |= V(1, 0);
  else if (errno == ENOMEM &&
           (a[0] = ma_create_full(128, 128, 128, t_forward, y_forward, q0)) != NULL)
    visited |= V(2, 0);
  else
    return visited |= V(4, 0); // To nie powinno się wykonać.

  errno = 0;
  if ((a[1] = ma_create_full(128, 128, 128, t_forward, y_forward, q1)) != NULL)
    visited |= V(1, 1);
  else if (errno == ENOMEM &&
           (a[1] = ma_create_full(128, 128, 128, t_forward, y_forward, q1)) != NULL)
    visited |= V(2, 1);
  else
    return visited |= V(4, 1); // To nie powinno się wykonać.

  errno = 0;
  if (ma_connect(a[1], 0, a[0], 0, 128) == 0)
    visited |= V(1, 6);
  else if (errno == ENOMEM && ma_connect(a[1], 0, a[0], 0, 128) == 0)
    visited |= V(2, 6);
  else
    return visited |= V(4, 6); // To nie powinno się wykonać.

  assert(ma_set_input(a[0], x0) == 0);
  assert((y1 = ma_get_output(a[1])));
  assert(y1[0] == q1[0] && y1[1] == q1[1]);

  errno = 0;
  if (ma_step(a, SIZE(a)) == 0)
    visited |= V(1, 7);
  else if (errno == ENOMEM && ma_step(a, SIZE(a)) == 0)
    visited |= V(2, 7);
  else
    return visited |= V(4, 7); // To nie powinno się wykonać.

  assert(y1[0] == q0[0] && y1[1] == q0[1]);

  errno = 0;
  if (ma_step(a, SIZE(a)) == 0)
    visited |= V(1, 8);
  else if (errno == ENOMEM && ma_step(a, SIZE(a)) == 0)
    visited |= V(2, 8);
  else
    return visited |= V(4, 8); // To nie powinno się wykonać.

  assert(y1[0] == x0[0] && y1[1] == x0[1]);
  assert(ma_disconnect(a[1], 62, 4) == 0);
  assert(ma_set_input(a[1], x1) == 0);

  errno = 0;
  if (ma_step(a, SIZE(a)) == 0)
    visited |= V(1, 9);
  else if (errno == ENOMEM && ma_step(a, SIZE(a)) == 0)
    visited |= V(2, 9);
  else
    return visited |= V(4, 9); // To nie powinno się wykonać.

  assert(y1[0] == y0[0] && y1[1] == y0[1]);

  ma_delete(a[0]);
  ma_delete(a[1]);

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
  return memory_test(alloc_fail_test_example);
}

// Testuje reakcję implementacji na niepowodzenie alokacji pamięci.
static int weak(void) {
  return memory_test(alloc_fail_test_advanced);
}

// Testuje reakcję implementacji na niepowodzenie alokacji pamięci.
static int disconnect(void) {
  return memory_test(alloc_fail_test_disconnect);
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
  TEST(connections),
  TEST(undetermined),
  TEST(delete),
  TEST(params),
  TEST(malicious),
  TEST(pipeline),
  TEST(shift),
  TEST(cycle),
  TEST(alloc),
  TEST(memory),
  TEST(weak),
  TEST(disconnect)
};

static int do_test(int (*function)(void)) {
  int result = function();
  puts("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef");
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
