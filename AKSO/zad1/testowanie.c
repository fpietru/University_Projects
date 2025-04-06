#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include "ma.h"

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

void t_one(uint64_t *next_state, uint64_t const *input,
  uint64_t const *old_state, size_t, size_t) {
next_state[0] = old_state[0] + input[0];
}

void y_one(uint64_t *output, uint64_t const *state, size_t, size_t) {
output[0] = state[0] + 1;
}

int main () {

  const uint64_t q1 = 1, x3 = 3, *y;

  moore_t *a = ma_create_full(64, 64, 64, t_one, y_one, &q1);
  assert(a);

  y = ma_get_output(a);
  ASSERT(y != NULL);
  ASSERT(ma_set_input(a, &x3) == 0);
  // ASSERT(y[0] == 2);
  printf("%d", y[0]);
  /*ASSERT(ma_step(&a, 1) == 0);
  ASSERT(y[0] == 5);
  ASSERT(ma_step(&a, 1) == 0);
  ASSERT(y[0] == 8);
  ASSERT(ma_set_input(a, &q1) == 0);
  ASSERT(ma_set_state(a, &x3) == 0);
  ASSERT(y[0] == 4);
  ASSERT(ma_step(&a, 1) == 0);
  ASSERT(y[0] == 5);
  ASSERT(ma_step(&a, 1) == 0);
  ASSERT(y[0] == 6); */

  ma_delete(a);

  return 0;
}