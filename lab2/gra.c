#include <stdio.h>
#define LIMIT 1003

int wynik[LIMIT][LIMIT];

void swap(int *a, int *b) {
    *b ^= *a;
    *a ^= *b;
    *b ^= *a;
}

int nwd(int a, int b) {
    return (b == 0 ? a : nwd(b, a % b));
}

void zapamietaj(int a, int b, int c) {
    if (a < LIMIT && wynik[a][b] == 0)
        wynik[a][b] = c;
}

int jakapozycja(int a, int b) {
    if (a < b) swap(&a, &b);
    if (a < LIMIT && wynik[a][b] != 0) {
        return wynik[a][b] - 1;
    }
    printf("%d %d\n", a, b);

    if (a == 1 && b == 1) {
        zapamietaj(1, 1, 1);
        return 0;
    }
    if (b == 1) {
        int res = (a % 2 == 0 ? 1 : 0);
        zapamietaj(a, 1, res + 1);
        return res;
    }
    int d = nwd(a-1, b);
    int opcja1 = jakapozycja((a-1)/d, b/d);
    zapamietaj((a-1)/d, b/d, opcja1+1);
    int opcja2 = 0;
    if (b > 1) {
        d = nwd(a, b-1);
        opcja2 = jakapozycja(a/d, (b-1)/d);
        zapamietaj(a/d, (b-1)/d, opcja2+1);
    }
    return (opcja1 + opcja2 == 0);
}

/*
int graj(int a, int b) {


} */

int main () {

    printf("%d\n", jakapozycja(1237,123));

    return 0;
}