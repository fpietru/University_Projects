#include <stdio.h>
#include <stdlib.h>

int* zsumuj(int n, int a[]) {
    int* pref = (int*)malloc((n+1)*(sizeof(int)));
    int* res = (int*)malloc(n*(sizeof(int)));

    pref[0] = 0;
    for (int i=1; i<=n; i++) {
        pref[i] = pref[i-1] + a[i-1];
    }
    for (int i=0; i<n; i++) {
        if (a[i] > n) res[i] = 0;
        else {
            res[i] = pref[n] - pref[a[i]-1];
        }
    }
    return res;
}

int main () {

    int n = 6;
    int a[] = {1, 3, 7, 8, 90, 100};
    int* res = zsumuj(n, a);
    for (int i=0; i<n; i++)
        printf("%d ", res[i]);
    printf("\n");

    return 0;
}