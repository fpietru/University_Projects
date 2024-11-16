#include "gra.h"
#include <stdio.h>

int main () {
    int n = 10;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++)
            printf("(%d, %d): %d\n", i, j, graj(i, j));
    }
}