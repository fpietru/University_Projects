#include <stdio.h>

int swap(int *a, int *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

int nwd(int a, int b) {
    return (b == 0 ? a : nwd(b, a%b));
}

int pozycja(int a, int b) {
    if (a < b) swap(&a, &b);
    if (a == 1 && b == 1)
        return 0;
    
    int na, nb, d;
    int op1, op2;

    // opcja 1
    d = nwd(a-1, b);
    na = (a-1) / d;
    nb = b / d;
    op1 = pozycja(na, nb);

    if (op1 == 0)
        return 1;
    
    // opcja 2
    if (b > 1) {
        d = nwd(a, b-1);
        na = a / d;
        nb = (b-1) / d;
        op2 = pozycja(na, nb);
    }
    else {
        return 0;
    }

    if (op2 == 0)
        return 1;
    else return 0;
}

int main() {

    int L = 100;
    int R = 110;
    for (int i=L; i<=R; i++) {
        for (int j=L; j<=R; j++)
            printf("%d", pozycja(i, j));       
        printf("\n");
    }

    return 0;
}