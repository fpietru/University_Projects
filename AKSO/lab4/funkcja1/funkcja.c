#include <stdio.h>

// To jest deklaracja funkcji.
void funkcja(int, long);

// To jest deklaracja funkcji.
void funkcja(int x, long y);

// To jest definicja funkcji.
void funkcja(int a, long b) {
  printf("Funkcja została wywołana z parametrami %d, %ld.\n", a, b);
}
