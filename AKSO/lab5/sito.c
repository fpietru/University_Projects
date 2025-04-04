/*
 * Sito Eratostenesa (ang. sieve of Eratosthenes) jest prostym algorytmem
 * znajdowania liczb pierwszych. Szczegoly algorytmu mozna poznac, przegladajac
 * strone https://pl.wikipedia.org/wiki/Sito_Eratostenesa .
 *
 * Brak polskich znakow wynika z braku (domyslnego) wsparcia dla unikodu przez
 * DDD.
 */

#include <stdbool.h>
#include <stdio.h>

static void sieve_init(bool *s, int n) {
  for (int i = 2; i < n; ++i) {
    s[i] = true;
  }
}

static void sieve(bool *s, int n) {
  for (int i = 2; i < n; ++i) {
    if (s[i]) {
      printf("%d\n", i);
      int j = i;
      while (j < n - i) { // Uwaga na przypadek, gdy np. n = INT_MAX.
        j += i;
        s[j] = false;
      }
    }
  }
}

static void sieve_destroy(bool *s, int n) {
  // Nic szczegolnego do zrobienia (tym razem).
  (void)s; // W ten sposob pozbywamy sie ostrzezenia o nieuzywanym parametrze.
  (void)n;
}

int main() {
  const int n = 10;
  bool s[n];
  sieve_init(s, n);
  sieve(s, n);
  sieve_destroy(s, n);
  return 0;
}
