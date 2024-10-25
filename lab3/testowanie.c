#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "zbior_ary.h"

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
    // g = {1, 2, 4, 7, 9, 12, 19}
    zbior_ary G = roznica(E, F);
    assert(ary(G) == 4);
    // H = {4, 9, 19};
    zbior_ary H = iloczyn(G, B);
    assert(moc(H) == 3);
    assert(ary(H) == 2);
    // I = {}
    zbior_ary I = iloczyn(H, A);
    assert(moc(I) == 0);

/*
    zbior_ary A1 = ciag_arytmetyczny(2, 2, 8);
    zbior_ary A2 = ciag_arytmetyczny(10, 2, 20);
    zbior_ary A3 = ciag_arytmetyczny(1, 2, 5);
    zbior_ary A4 = ciag_arytmetyczny(9, 2, 13);
    zbior_ary A = suma(suma(suma(A4, A3), A2), A1);

    informacja(A1);
    informacja(A2);
    informacja(A3);
    informacja(A4);
    informacja(A);

    zbior_ary B1 = ciag_arytmetyczny(4, 2, 6);
    zbior_ary B2 = ciag_arytmetyczny(8, 2, 12);
    zbior_ary B3 = ciag_arytmetyczny(1, 2, 11);
    zbior_ary B4 = ciag_arytmetyczny(21, 2, 21);
    zbior_ary B = suma(suma(B3,B2), suma(B4, B1));

    informacja(B1);
    informacja(B2);
    informacja(B3);
    informacja(B4);
    informacja(B);

    zbior_ary C = roznica(A, B);
    informacja(C); */


    /*
    // A = {2, 7, 12}
    zbior_ary A = ciag_arytmetyczny(2, 5, 12);
    informacja(A);
    // B = {4, 9, 14, 19}
    zbior_ary B = ciag_arytmetyczny(4, 5, 19);
    informacja(B);
    // C = {1}
    zbior_ary C = singleton(1);
    informacja(C);
    // D = {1, 4, 9, 14, 19}
    zbior_ary D = suma(B, C);
    informacja(D);
    // E = {1, 2, 4, 7, 9, 12, 14, 19}
    zbior_ary E = suma(D, A);
    informacja(E);
    // F = {14}
    zbior_ary F = singleton(14);
    informacja(F);
    // g = {1, 2, 4, 7, 9, 12, 19}
    zbior_ary G = roznica(E, F);
    informacja(G);
    */

    return 0;
}