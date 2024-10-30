#include <stdio.h>
#include <stdlib.h>

#include "zbior_ary.h"
int main() {
  zbior_ary *zbior = (zbior_ary *)malloc(1000000U * sizeof(zbior_ary));
  zbior[0] = ciag_arytmetyczny(15, 2, 17);
  zbior[1] = ciag_arytmetyczny(12, 2, 16);
  zbior[2] = singleton(4);
  zbior[3] = roznica(zbior[2], zbior[2]);
  zbior[4] = suma(zbior[2], zbior[0]);
  zbior[5] = iloczyn(zbior[4], zbior[2]);
  printf("%d\n", nalezy(zbior[5], 6));
  printf("%d\n", nalezy(zbior[0], 14));
  printf("%u\n", ary(zbior[3]));
  printf("%u\n", moc(zbior[0]));

  for (int k=0; k<=5; k++) {
    printf("z%d: ", k);
  
    for (int i=1; i<=100; i++)
      if (nalezy(zbior[k], i))
        printf("%d ", i);
    printf("\n");
  
  }

  return 0;
}