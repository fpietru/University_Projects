#include <inttypes.h>
#include <stdio.h>

#define SIZE(x) (sizeof x / sizeof x[0])

// To jest deklaracja testowanej funkcji.
uint64_t mac0(uint64_t a, uint64_t x, uint64_t y);

typedef struct {
  uint64_t const a;
  uint64_t const x;
  uint64_t const y;
  uint64_t const w;
} test_mac0_values_t;

static test_mac0_values_t test_mac0[] = {
  {0, 0, 0, 0},
  {1, 1, 1, 2},
  {5, 7, 11, 82},
  {0, 0x100000000, 0x100000000, 0},
  {0xffffffffffffffff, 1, 1, 0},
  {0xfffffffffffffff0, 5, 5, 9},
  {0xffffffffffffffff, 0x100000002, 0x100000002, 0x400000003},
};

static void print__64(char const *s, uint64_t x) {
  printf("%s %016" PRIx64 "\n", s, x);
}

int main() {
  for (size_t i = 0; i < SIZE(test_mac0); ++i) {
    uint64_t w = mac0(test_mac0[i].a, test_mac0[i].x, test_mac0[i].y);
    if (w == test_mac0[i].w) {
      printf("mac0 test %zu pass\n", i);
    }
    else {
      printf("mac0 test %zu fail\n", i);
      print__64("a             = ", test_mac0[i].a);
      print__64("x             = ", test_mac0[i].x);
      print__64("y             = ", test_mac0[i].y);
      print__64("mac should be = ", test_mac0[i].w);
      print__64("mac is        = ", w);
    }
  }
}
