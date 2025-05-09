#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// To jest deklaracja testowanej funkcji.
uint64_t delay(uint64_t);

int main(int argc, char *args[]) {
  if (argc < 2) {
    fprintf(stderr, "Użyj:\n%s liczba_iteracji\n", args[0]);
    return 1;
  }

  // Pomijamy sprawdzanie błędów.
  uint64_t n = strtoull(args[1], NULL, 10);

  // Załaduj kod funkcji do pamięci podręcznej.
  delay(2);

  // Wykonaj właściwy test.
  uint64_t t = delay(n);

  // Wypisz wynik testu.
  printf("Średnia liczba cykli zegara na jedną iterację pętli wynosi %.2f.\n",
         (double)(t) / (double)n);
}
