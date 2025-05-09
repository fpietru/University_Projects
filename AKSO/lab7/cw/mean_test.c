#include <assert.h>
#include <stdint.h>

// To jest deklaracja testowanej funkcji.
uint64_t mean(uint64_t, uint64_t);

int main() {
  static const uint64_t m = 0x100000000;

  assert(mean(0, 0) == 0);
  assert(mean(2, 6) == 4);
  assert(mean(1, 4) == 2);
  assert(mean(11, 15) == 13);
  assert(mean(UINT64_MAX, UINT64_MAX) == UINT64_MAX);
  assert(mean(UINT64_MAX - 1, UINT64_MAX) == UINT64_MAX - 1);
  assert(mean(UINT64_MAX - 4, UINT64_MAX - 2) == UINT64_MAX - 3);
  assert(mean(UINT64_MAX - 4, UINT64_MAX - 1) == UINT64_MAX - 3);
  assert(mean(UINT64_MAX / 2 + 1, UINT64_MAX / 2 + 1) == UINT64_MAX / 2 + 1);
  assert(mean(UINT64_MAX / 2 + 1, UINT64_MAX / 2 + 3) == UINT64_MAX / 2 + 2);
  assert(mean(UINT64_MAX / 2 + 1, UINT64_MAX / 2 + 4) == UINT64_MAX / 2 + 2);
  assert(mean(UINT64_MAX / 2 + 1, UINT64_MAX / 2 - 5) == UINT64_MAX / 2 - 2);
  assert(mean(m, m) == m);
  assert(mean(m, m + 1) == m);
  assert(mean(m + 1, m) == m);
  assert(mean(m - 1, m + 1) == m);
}
