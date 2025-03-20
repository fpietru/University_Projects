#include <stdio.h>

// To jest deklaracja funkcji.
int funkcja(char *);

int main() {
  // To jest użycie funkcji.
  int w = funkcja("Ala ma kota.");

  printf("Wynikiem funkcji jest %d.\n", w);
}
