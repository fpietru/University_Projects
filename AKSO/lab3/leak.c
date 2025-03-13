#include <stdlib.h>

int main() {
  int *x;

  x = (int*)malloc(sizeof(int));
  x = (int*)malloc(sizeof(int));
  free(x);

  return 0;
}
