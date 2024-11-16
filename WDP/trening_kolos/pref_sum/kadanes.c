#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b));

int p(int n, int t[]) {
    int suma = 0;
    int res = 0;
    for (int i=0; i<n; i++) {
        suma = max(t[i], suma + t[i]);
        res = max(res, suma);
    }
    return res;
}


int main () {

    int n = 7;
    int a[] = {2, 3, -8, 7, -1, 2, 3};
    printf("%d\n", p(n, a));

    return 0;
}