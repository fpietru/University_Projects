#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "zbior_ary.h"
#include <stdlib.h>

void wypisz(zbior_ary A) {
    for (int i=-300; i<=300; i++)
        if (nalezy(A, i))
            printf("%d ", i);
    printf("\n");
}

int RAND(int a, int b) {
    return a + rand() % (b-a+1);
}

int main() {
    /* int a1, q1, b1;
    scanf("%d %d %d", &a1, &q1, &b1);
    int a2, q2, b2;
    scanf("%d %d %d", &a2, &q2, &b2);

    zbior_ary A = ciag_arytmetyczny(a1, q1, b1);
    zbior_ary B = ciag_arytmetyczny(a2, q2, b2);
    zbior_ary C = suma(A, B);
    zbior_ary D = roznica(A, B);
    zbior_ary E = iloczyn(A, B);

    wypisz(A);
    wypisz(B);
    wypisz(C);
    wypisz(D);
    wypisz(E); */

    int LIMIT = 1000000;
    
    zbior_ary *zbior = (zbior_ary *)malloc(1000000U * sizeof(zbior_ary));
        
    for (int i=1; i<LIMIT; i++) {
        zbior[i] = ciag_arytmetyczny(RAND(-200, -100), 1, RAND(1, 1000));
    }

    for (int i=1; i<LIMIT; i++) {
        zbior[i] = roznica(zbior[i], zbior[i-1]);
    }


    return 0;
}