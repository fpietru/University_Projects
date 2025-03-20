#include <stdio.h>
#include <stdlib.h>
#include "input-output.h"

int read_int(void) {
  int value, result;

  result = scanf("%d", &value);

  // Trzeba coś zrobić, gdy czytanie się nie powiedzie.
  if (result != 1)
    exit(1);

  return value;
}

void print_uint(unsigned int value) {
  printf("%u\n", value);
}
