#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// return 1 iff A >= B
int compare(uint64_t *A, uint64_t *B, unsigned sz) {
  for (int i=sz-1; i>=0; i--) {
    if (A[i] > B[i])
      return 1;

    if (A[i] < B[i])
      return 0;
  }
  return 1;
}

// A -= B when A >= B
void sub(uint64_t *A, uint64_t *B, unsigned sz) {
  uint64_t borrow = 0;
  for (unsigned i=0; i<sz; i++) {
    uint64_t ai = A[i] - borrow;
    uint64_t bi = B[i];
    borrow = (ai < bi);
    A[i] = ai - bi;
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

void r_shift(uint64_t *T, uint64_t *Q, unsigned sz, unsigned k) {
  unsigned l = k / 64;
  unsigned r = k % 64;

  for (int i=sz-1; i>=0; i--) {
    T[i+l] = Q[i] << r;
    if (r && i+l+1 < 2*sz) {
      T[i+l+1] |= Q[i] >> (64-r);
    }
  }
}

void nsqrt(uint64_t *Q, uint64_t *X, unsigned n) {
  unsigned sz = n / 64;

  uint64_t *T = calloc(2*sz, sizeof(uint64_t));

  for (unsigned i=0; i<sz; i++) {
    Q[i] = 0;
  }

  for (unsigned j=1; j<=n; j++) {
    for (unsigned i=0; i<2*sz; i++) {
      T[i] = 0;
    }

    r_shift(T, Q, sz, n-j+1);
    add_bit(T, 2*sz, 2*n - 2*j);
    
    if (compare(X, T, 2*sz)) {
      add_bit(Q, sz, n-j);
      sub(X, T, 2*sz);
    }
  }

  free(T);
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

  wypisz(X, n);

  nsqrt(Q, X, n);

  wypisz(Q, n);



  return 0;
}