#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool rozne(int n, int a[]) {
    int i=0, j=n-1;
    while (i<j) {
        if (a[i] == a[j])
            return false;
        if (a[i] >= a[j]) i++;
        else j--;
    }
    return true;
}

int main () {
    int n = 9;
    int a[] = {40, 10, 1, -5, -3, 1, 8, 20, 34};
    printf("%d\n", rozne(n, a));

    return 0;
}