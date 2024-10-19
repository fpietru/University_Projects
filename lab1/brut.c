#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a>=b ? a : b);
}

int main () {
    int n;
    scanf("%d", &n);

    int *tab = (int*)malloc(n*sizeof(n));

    for (int i=0; i<n; i++) {
        scanf("%d", &tab[i]);
    }

    int ans = 1;
    for (int j=0; j<n; j++) {
        int i=j;
        while (i-1>=0 && tab[i-1] != 0 && tab[j] % tab[i-1] == 0 )
            i--;
        ans = max(ans, j-i+1);
    }

    printf("%d\n", ans);

    return 0;
}