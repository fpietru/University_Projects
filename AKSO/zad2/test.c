#include <inttypes.h>
#include <stdlib.h>

void nsqrt(uint64_t *Q, uint64_t *X, unsigned n) {
  unsigned s = n / 64;
  unsigned ss = s << 1;
  static uint64_t T[8000];

  for (unsigned i=0; i<s; i++) {
    Q[i] = 0;
  }

  for (unsigned j=1; j<=n; j++) {
    
    for (unsigned i=0; i<ss; i++) {
      T[i] = 0;
    }

    // r_shift(T, Q, s, n-j+1);
    unsigned k = n - j + 1;
    unsigned l = k / 64;
    unsigned r = k % 64;
    for (int i=s-1; i>=0; i--) {
        T[i+l] = Q[i] << r;
        if (r && i+l+1 < ss) {
            T[i+l+1] |= Q[i] >> (64-r);
        }
    }

    // add_bit(T, ss, 2*n - 2*j);
    k = 2*n - 2*j;
    uint64_t carry = (1ULL << (k % 64));
    for (unsigned i=k/64; i<ss; i++) {
        uint64_t before = T[i];
        T[i] += carry;
        if (T[i] >= before) {
          break;
        }
        carry = 1;
    }

    int is_x_geq_t = 1;
    // compare(X, T, ss)
    for (int i=ss-1; i>=0; i--) {
        if (X[i] > T[i]) {
            break;
        } else if (X[i] < T[i]) {
            is_x_geq_t = 0;
            break;
        }
    }
    
    if (is_x_geq_t) {
      // add_bit(Q, s, n-j);
      k = n-j;
      uint64_t carry = (1ULL << (k % 64));
      for (unsigned i=k/64; i<s; i++) {
        uint64_t before = Q[i];
        Q[i] += carry;

        if (Q[i] >= before) {
          break;
        }
        carry = 1;
      }
      
      // sub(X, T, ss);
      uint64_t borrow = 0;
      for (unsigned i=0; i<ss; i++) {
        uint64_t xi = X[i] - borrow;
        uint64_t ti = T[i];
        borrow = (xi < ti);
        X[i] = xi - ti;
      }
    }
  }
}
