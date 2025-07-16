#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define min(a, b) ((a) < (b) ? (a) : (b));

int malo(int n, int t[]) {
    int i=0, j=n-1;
    int res = INT_MAX;
    while (i < j) {
        int suma = t[i] + t[j];
        res = min(res, abs(suma));
        if (suma > 0) j--;
        else i++;
    }
    return res;
}

int main () {

    int n = 8;
    int a[] = {-42, -12, -8, -1, -1, 5, 15, 60};
    printf("%d\n", malo(n, a));

    return 0;
}