#include <assert.h>

// To jest deklaracja testowanej funkcji.
unsigned counter(void);

int main() {
  for (unsigned i = 1; i < 100; ++i)
    assert(i == counter());
}
