#include <assert.h>
#include <limits.h>

// To jest deklaracja pierwszej z testowanych funkcji.
int smax(int, int);

// Funkcja umax ma deklarację
//  unsigned umax(unsigned, unsigned);
// ale w testach deklarujemy ją z 64-bitowymi argumentami,
// żeby sprawdzić, czy zostały użyte właściwe rejestry.
unsigned umax(unsigned long, unsigned long);

int main() {
  assert(smax(3, 7) == 7);
  assert(smax(1000, 765) == 1000);
  assert(smax(0, 256) == 256);
  assert(smax(255, 0) == 255);
  assert(smax(1, -1) == 1);
  assert(smax(-1, 1) == 1);
  assert(smax(INT_MAX, INT_MIN) == INT_MAX);
  assert(smax(777, 777) == 777);
  assert(smax(-777, -777) == -777);

  assert(umax(5, 9) == 9);
  assert(umax(9000, 5000) == 9000);
  assert(umax(-1, 1) == -1);
  assert(umax(1, -1) == -1);
  assert(umax(1000000000, 5000000000) == 1000000000);
  assert(umax(5000000000, 1000000000) == 1000000000);
  assert(umax(INT_MAX, INT_MIN) == INT_MIN);
  assert(umax(987, 987) == 987);
}
