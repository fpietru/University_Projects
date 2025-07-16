#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

int powtarzajaca_sie(int n, int a[]) {
    for (int i=0; i<=n; i++) {
        while (i+1 != a[i]) {
            int j = a[i] - 1;
            if (a[j] == a[i])
                return a[i];
            swap(&a[i], &a[j]);
        }
    }
    return -1;
}

int main () {

    int n = 5;
    int a[] = {1, 2, 3, 5, 4, 3};
    printf("%d\n", powtarzajaca_sie(n, a));

    return 0;
}