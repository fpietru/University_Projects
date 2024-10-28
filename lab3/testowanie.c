#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "zbior_ary.h"

void wypisz(zbior_ary A) {
    for (int i=1; i<=300; i++)
        if (nalezy(A, i))
            printf("%d ", i);
    printf("\n");
}

int main() {

    int a1, q1, b1;
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
    wypisz(E);

    // informacja(A);
    // informacja(D);
    // informacja(E);

    return 0;
}