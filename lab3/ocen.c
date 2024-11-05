#include <stdlib.h>
#include <stdio.h>
#include "zbior_ary.h"
#include <assert.h>


int main() {

  zbior_ary A = ciag_arytmetyczny(2, 5, 12);
  assert(moc(A) == 3);
  assert(ary(A) == 1);
  // B = {4, 9, 14, 19}
  zbior_ary B = ciag_arytmetyczny(4, 5, 19);
  // C = {1}
  zbior_ary C = singleton(1);
  // D = {1, 4, 9, 14, 19}
  zbior_ary D = suma(B, C);
  // E = {1, 2, 4, 7, 9, 12, 14, 19}
  zbior_ary E = suma(D, A);
  assert(moc(E) == 8);
  // F = {14}
  zbior_ary F = singleton(14);
  // G = {1, 2, 4, 7, 9, 12, 19}
  zbior_ary G = roznica(E, F);
  assert(ary(G) == 4);
  assert(nalezy(G, 4));
  assert(!nalezy(G, 5));
  // H = {4, 9, 19};
  zbior_ary H = iloczyn(G, B);
  assert(moc(H) == 3);
  assert(ary(H) == 2);
  // I = {}
  zbior_ary I = iloczyn(H, A);
  assert(moc(I) == 0);

  // zbior_ary *zbior = (zbior_ary *)malloc(1000000U * sizeof(zbior_ary));
  /*zbior[0] = ciag_arytmetyczny(48, 2, 84); // {(48, 84, 0)}
  zbior[1] = singleton(13); // {(13, 13, 1)}
  printf("1) %u\n", moc(zbior[1])); // 1
  zbior[2] = singleton(38); // {(38, 38, 0)}
  zbior[3] = suma(zbior[1], zbior[0]); // {(48, 84, 0), (13, 13, 1)}
  zbior[4] = suma(zbior[3], zbior[0]); // {(48, 84, 0), (13, 13, 1)}
  zbior[5] = suma(zbior[1], zbior[1]); // {(13, 13, 1)}
  printf("2) %u\n", ary(zbior[2])); // 1
  zbior[6] = ciag_arytmetyczny(0, 2, 0); // {(0, 0, 0)} 
  zbior[7] = iloczyn(zbior[5], zbior[0]); // {(1, -1, 0)}
  printf("3) %u\n", ary(zbior[1])); // 1
  zbior[8] = singleton(22); // {(22, 22, 0)}
  printf("4) %d\n", nalezy(zbior[1], 11)); // 0
  printf("5) %u\n", ary(zbior[0])); // 1
  zbior[9] = suma(zbior[2], zbior[8]); // {(22, 22, 0), (38, 38, 0)}
  zbior[10] = iloczyn(zbior[0], zbior[4]); // {(48, 84, 0)}
  zbior[11] = ciag_arytmetyczny(84, 2, 100); // {(84, 100, 0)}
  zbior[12] = iloczyn(zbior[0], zbior[5]); // {(1, -1, 0)}
  zbior[13] = singleton(29); // {(29, 29, 1)}
  zbior[14] = roznica(zbior[6], zbior[1]); // {(0, 0, 0)} 
  printf("6) %u\n", moc(zbior[7])); // 0
  zbior[15] = suma(zbior[7], zbior[4]); // {(48, 84, 0), (13, 13, 1)}
  zbior[16] = suma(zbior[14], zbior[7]); // {(0, 0, 0)}
  printf("7) %u\n", ary(zbior[4])); // 2
  zbior[17] = ciag_arytmetyczny(12, 2, 76); // {(12, 76, 0)}
  printf("8) %u\n", ary(zbior[13])); // 1
  printf("9) %u\n", ary(zbior[9])); // 2
  printf("10) %d\n", nalezy(zbior[11], 22)); // 0
  printf("11) %d\n", nalezy(zbior[2], 36)); // 0
  zbior[18] = singleton(91); // {(91, 91, 1)}
  printf("12) %d\n", nalezy(zbior[3], 43)); // 0
  zbior[19] = singleton(27); // {(27, 27, 1)}
  printf("13) %u\n", ary(zbior[11])); // 1
  zbior[20] = ciag_arytmetyczny(1, 2, 61); // {(1, 61, 1)}
  printf("14) %d\n", nalezy(zbior[10], 73)); // 0
  zbior[21] = roznica(zbior[15], zbior[0]); // {(13, 13, 1)}
  printf("15) %d\n", nalezy(zbior[19], 47)); // 0
  zbior[22] = roznica(zbior[20], zbior[6]); // {(1, 61, 1)}
  zbior[23] = suma(zbior[19], zbior[19]); // {(27, 27, 1)}
  printf("16) %u\n", ary(zbior[23])); // 1
  zbior[24] = ciag_arytmetyczny(17, 2, 37);
  zbior[25] = ciag_arytmetyczny(42, 2, 58);
  zbior[26] = ciag_arytmetyczny(18, 2, 96);
  zbior[27] = ciag_arytmetyczny(48, 2, 82);
  zbior[28] = suma(zbior[9], zbior[4]); // {(22, 22, 0), (38, 38, 0), (48, 84, 0), (13, 13, 1)}
  printf("17) %u\n", moc(zbior[2])); // 1
  printf("18) %d\n", nalezy(zbior[5], 39)); // 0
  zbior[29] = suma(zbior[16], zbior[25]); // {(0, 0, 0), (42, 58, 0)}
  printf("19) %u\n", moc(zbior[17])); // 33
  zbior[30] = roznica(zbior[26], zbior[28]); // {(18, 96, 0)} */

  /*zbior[1] = ciag_arytmetyczny(18, 2, 96);
  zbior[2] = suma(suma(suma(singleton(22), singleton(38)), ciag_arytmetyczny(48, 2, 84)), singleton(13));
  zbior[3] = roznica(zbior[1], zbior[2]); */


/*
  10 1
NEW_SET -1 7
NEW_SET -7 -6
SUM 0 1
NEW_SET 10 11
NEW_SET 7 16
SUM 2 3
NEW_SET -2 7
SUM 3 4
NEW_SINGLETON 2
SUM 5 4
SIZE */

/*  zbior[0] = ciag_arytmetyczny(-1, 1, 7);
  informacja(zbior[0]);
  zbior[1] = ciag_arytmetyczny(-7, 1, -6);
  informacja(zbior[1]);
  zbior[2] = suma(zbior[0], zbior[1]);
  informacja(zbior[2]);
  zbior[3] = ciag_arytmetyczny(10, 1, 11);
  informacja(zbior[3]);
  zbior[4] = ciag_arytmetyczny(7, 1, 16);
  informacja(zbior[4]);
  zbior[5] = suma(zbior[2], zbior[3]);
  informacja(zbior[5]);
  zbior[6] = ciag_arytmetyczny(-2, 1, 7);
  informacja(zbior[6]);
  zbior[7] = suma(zbior[3], zbior[4]);
  informacja(zbior[7]);
  zbior[8] = singleton(2);
  informacja(zbior[8]);
  zbior[9] = suma(zbior[5], zbior[4]);
  informacja(zbior[9]); */

  /*zbior[10] = ciag_arytmetyczny(-1, 1, 7);
  zbior[11] = ciag_arytmetyczny(7, 1, 16);
  zbior[12] = suma(zbior[10], zbior[11]); */


/*
10 2
NEW_SET 4 12
NEW_SET -4 -4
NEW_SINGLETON 7
NEW_SET 1 3
SUM 2 3
SUM 2 3
NEW_SET -3 5
NEW_SET 6 6
NEW_SET 2 6
SUM 5 6
SIZE
 */
  
  /*
  zbior[0] = ciag_arytmetyczny(4, 2, 12);
  informacja(zbior[0]);
  zbior[1] = ciag_arytmetyczny(-4, 2, -4);
  informacja(zbior[1]);
  zbior[2] = singleton(7);
  informacja(zbior[2]);
  zbior[3] = ciag_arytmetyczny(1, 2, 3);
  informacja(zbior[3]);
  zbior[4] = suma(zbior[2], zbior[3]);
  informacja(zbior[4]);
  zbior[5] = suma(zbior[2], zbior[3]);
  informacja(zbior[5]);
  zbior[6] = ciag_arytmetyczny(-3, 2, 5);
  informacja(zbior[6]);
  zbior[7] = ciag_arytmetyczny(6, 2, 6);
  informacja(zbior[7]);
  zbior[8] = ciag_arytmetyczny(2, 2, 6);
  informacja(zbior[8]);
  zbior[9] = suma(zbior[5], zbior[6]);
  informacja(zbior[9]);
  */


/*
  for (int k=0; k<=29; k++) {
    printf("%d [%d] (%d): ", k, moc(zbior[k]), ary(zbior[k]));
    for (int i=-100; i<=100; i++)
      if (nalezy(zbior[k], i))
        printf("%d ", i);
    printf("\n");
  }
*/
  return 0;
}