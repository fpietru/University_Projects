#include <stdio.h>
#include <stdlib.h>

int minimum(int n, int a[]) {
    int l=0, r = n-1;
    while (l < r) {
        int m = (l + r) / 2;
        if (a[m+1] - a[m] > 0)
            r = m;
        else l = m+1;
    }
    return a[l];
}

int main () {
    int n = 9;
    int a[] = {40, 10, 1, -5, -3, 1, 8, 20, 34};
    printf("%d\n", minimum(n, a));

    return 0;
}