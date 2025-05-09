#include <inttypes.h>
#include <stdio.h>

#define SIZE(x) (sizeof x / sizeof x[0])

typedef struct {  // To jest architektura cienkokońcówkowa.
  uint64_t lo;    // Młodze 64 bity będą umieszczone pod mniejszym adresem.
  uint64_t hi;    // Starsze 64 bity będą umieszczone pod większym adresem.
} uint128_t;

// To jest deklaracja testowanej funkcji.
void mac2(uint128_t *a, uint128_t const *x, uint128_t const *y);

typedef struct {
  uint128_t a;
  uint128_t const x;
  uint128_t const y;
  uint128_t const w;
} test_mac2_values_t;

static test_mac2_values_t test_mac2[] = {
  {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
  {
    {       0x500000005,        0x600000006},
    {       0x100000001,        0x200000002},
    {       0x300000003,        0x400000004},
    {       0xb00000008,       0x1a00000013}
  },
  {
    {0xffffffffffffffff,                0x0},
    {               0x1,                0x0},
    {               0x1,                0x0},
    {               0x0,                0x1}
  },
  {
    {               0x0, 0xffffffffffffffff},
    {       0x100000000,                0x0},
    {       0x100000000,                0x0},
    {               0x0,                0x0}
  },
  {
    {               0x0,                0x0},
    {0xffffffffffffffff, 0xffffffffffffffff},
    {0xffffffffffffffff, 0xffffffffffffffff},
    {               0x1,                0x0}
  },
  {
    {0x1000000000000000,                0x0},
    {0xffffffffffffffff,                0x0},
    {               0x2,                0x0},
    { 0xffffffffffffffe,                0x2}
  },
  {
    {               0x0,                0x0},
    {               0x1,                0x0},
    {0xffffffffffffffff,                0x0},
    {0xffffffffffffffff,                0x0}
  },
};

static void print_128(char const *s, uint128_t x) {
  printf("%s %016" PRIx64 "%016" PRIx64 "\n", s, x.hi, x.lo);
}

int main() {
  for (size_t i = 0; i < SIZE(test_mac2); ++i) {
    uint128_t a_org = test_mac2[i].a;
    mac2(&test_mac2[i].a, &test_mac2[i].x, &test_mac2[i].y);
    if (test_mac2[i].a.lo == test_mac2[i].w.lo &&
        test_mac2[i].a.hi == test_mac2[i].w.hi) {
      printf("mac2 test %zu pass\n", i);
    }
    else {
      printf("mac2 test %zu fail\n", i);
      print_128("a             = ", a_org);
      print_128("x             = ", test_mac2[i].x);
      print_128("y             = ", test_mac2[i].y);
      print_128("mac should be = ", test_mac2[i].w);
      print_128("mac is        = ", test_mac2[i].a);
    }
  }
}
