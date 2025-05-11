#include <assert.h>

// To jest deklaracja testowanej funkcji.
int caller(int (*callback)(int), int x);

// To jest deklaracja funkcji wołanej przez testowaną funkcję.
int called(int x);

int main() {
  for (int i = 1; i < 100; ++i)
    assert(i + 1 == caller(called, i));
}
