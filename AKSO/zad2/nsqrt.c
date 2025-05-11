#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <inttypes.h>
#include <stdlib.h>


void wypisz(uint64_t *T, unsigned s) {
  printf("===\n");
  for (unsigned i=0; i<s; i++) {
    printf("%d: ", i);
    for (unsigned j=0; j<64; j++) {
      printf("%d", ((T[i] & (1ULL<<j)) > 0));
    }
    printf("\n");
  }
  printf("===\n");
}

void sub_bit(uint64_t *X, unsigned ss, unsigned k) {
  uint64_t borrow = (1ULL << (k % 64));
  for (unsigned i=k/64; i<ss; i++) {
    uint64_t before = X[i];
    X[i] -= borrow;
    if (X[i] <= before) {
      break;
    }
    borrow = 1;
  }
}

void add_bit(uint64_t *T, unsigned sz, unsigned k) {
  uint64_t carry = (1ULL << (k % 64));

  for (unsigned i=k/64; i<sz; i++) {
    uint64_t before = T[i];
    T[i] += carry;

    if (T[i] >= before) {
      break;
    }
    carry = 1;
  }
}

int main (int argc, char *argv[]) {

/*
  uint64_t *T = calloc(10, sizeof(uint64_t));

  T[0] = (1ULL<<64) - 1;
  T[4] = 8;

  wypisz(T, 10);

  add_bit(T, 10, 10);
  // r_shift(T, 10, 32+64);

  wypisz(T, 10); */

  int n = 1;
  uint64_t *Q, *X;
  Q = malloc(n * sizeof (uint64_t));
  X = malloc(2 * n * sizeof (uint64_t));

  X[0] = 15;
  X[1] = 0;

  wypisz(X, 2*n);

  sub_bit(X, 2, 5);

  wypisz(X, 2*n);

  add_bit(X, 2, 2);

  wypisz(X, 2*n);



  return 0;
}