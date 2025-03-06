#include <stdio.h>

static void sortuj(int *tablica, size_t n) {
  size_t i, j;
  int t;

  for (i = 0; i < n; ++i)
    for (j = 0; j < i; ++j)
      if (tablica[i] < tablica[j])
        t = tablica[i], tablica[i] = tablica[j], tablica[j] = t;
}

#define ROZMIAR_TABLICY 100

int main() {
  size_t i, n;
  int tablica[ROZMIAR_TABLICY];

  n = 0;
  while (scanf("%d", &tablica[n]) == 1)
    ++n;

  sortuj(tablica, n);

  for (i = 0; i < n; ++i)
    printf("%d\n", tablica[i]);

  return 0;
}
