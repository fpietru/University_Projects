#include <cassert>
#include <cinttypes>
#include <chrono>
#include <iostream>
#include <string>
#include <boost/multiprecision/gmp.hpp>

#include <bits/stdc++.h>

// To jest deklaracja testowanej funkcji.
extern "C" void nsqrt(uint64_t *Q, uint64_t *X, unsigned n);

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

using std::cout;
using std::cerr;
using std::stol;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using uint2n_t = boost::multiprecision::mpz_int;

namespace {
  // Funkcje konwertujÄce sÄ jawnie podane, aby pokazaÄ,
  // jakiego kodowania liczb wymaga funkcja nsqrt.

  template<typename T>
  void convert2bin(T in, uint64_t *out, size_t n) {
    for (size_t i = 0; i < n; ++i) {
      out[i] = (uint64_t)(in & UINT64_MAX);
      in >>= 64;
    }
  }

  template<typename T>
  void convert2boost(T &out, uint64_t const *in, size_t n) {
    out = 0;
    for (size_t i = n; i-- > 0;) {
      out <<= 64;
      out += in[i];
    }
  }
}

int maks_czas = 0;
void testuj(uint2n_t X, unsigned n){
  /*
  long k = stol(args[1]);
  unsigned n = k;
  uint2n_t X(args[2]), Q;

  if (X < 0)
    X += uint2n_t(1) << 2 * n;
  */
  uint2n_t Q;

  //assert(k % 64 == 0 && k >= 64 && k <= 256000);
  assert(n % 64 == 0 && n >= 64 && n <= 256000);
  assert(X >= 0 && X < uint2n_t(1) << 2 * n);

  // cout << "n = " << n << "\n"
  //     << "X = " << X << "\n";

  uint64_t *x = new uint64_t[n/32], *q = new uint64_t[n/64];

  convert2bin(X, x, n/32);

  auto begin = system_clock::now();

  nsqrt(q, x, n);

  auto end = system_clock::now();

  convert2boost(Q, q, n/64);

  delete[] x;
  delete[] q;

  int czas = (int)duration_cast<milliseconds>(end - begin).count();
  if(maks_czas < czas) maks_czas = czas;
  //cout << "Q = " << Q << "\n"
       //<< duration_cast<milliseconds>(end - begin).count() << " ms\n";

  bool git = (Q >= 0 && Q * Q <= X && Q * Q + Q >= X - Q);
  if(!git){
      cout << "Nie dziaĹa dla:\n";
      cout << X << "\n";
      cout << "Zwraca:\n";
      cout << Q << "\n";
      assert(0);
  }
}

std::mt19937 mt(2137);
int losuj(int a, int b){
    std::uniform_int_distribution<int> dist(a, b);
    return dist(mt);
}

uint64_t losuj64(){
    int t = losuj(0, 10);
    uint64_t ret = 0;
    for(int i = 0; i < 64; ++i){
        ret <<= 1;
        if(losuj(0, 10) < t) ++ret;
    }
    return ret;
}

uint2n_t losuj2n(unsigned n){
    uint2n_t t = 0;
    for(unsigned i = 0; i < (2*n)/64; ++i){
        t <<= 64;
        t += losuj64();
    }
    return t;
}

int main(){

    unsigned n_duze = 256000;
    unsigned n_male = 640;

    for(int i = 0; i < int(1e4); ++i){
        testuj(i, n_male);
    }

    testuj(uint2n_t(1)<<200, n_male);
    testuj((uint2n_t(1)<<200)-1, n_male);
    testuj(uint2n_t(1)<<(64*5), n_male);
    testuj((uint2n_t(1)<<(64*5))-1, n_male);

    for(int i = 0; i < int(1e4); ++i){
        testuj(losuj2n(n_male), n_male);
        uint2n_t t = losuj2n(n_male/2);
        t *= t;
        testuj(t, n_male);
        testuj(t-1, n_male);
    }

    for(int i = 0; i <3; ++i){
        testuj(losuj2n(n_duze), n_duze);
        uint2n_t t = losuj2n(n_duze/2);
        t *= t;
        testuj(t, n_duze);
        testuj(t-1, n_duze);
    }

    cout << "Maksymalny czas: " << maks_czas << "ms.\n";
}
