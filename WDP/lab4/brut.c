#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#define LIMIT 1000006
int siec[LIMIT];
int odleglosc[LIMIT];

int main () {
    int n;
    assert(scanf("%d", &n));
    for (int i=1; i<=n; i++) {
        assert(scanf("%d %d", &siec[i], &odleglosc[i]));
    }

    int mi = INT_MAX;
    int mx = 0;

    /*int best_pocz = -1;
    int best_mid = -1;
    int best_kon = -1; */

    for (int i=1; i<=n; i++) {
        for (int j=i; j<=n; j++) {
            for (int k=j; k<=n; k++) {
                if (siec[i] != siec[j] && siec[j] != siec[k] && siec[i] != siec[k]) {
                    int d1 = odleglosc[j] - odleglosc[i];
                    int d2 = odleglosc[k] - odleglosc[j];
                    // printf("%d %d %d %d %d\n", i, j, k, d1, d2);
                    mi = min(mi, max(d1, d2));
                    mx = max(mx, min(d1, d2));
                    // if (mx == min(d1, d2)) {
                        // best_pocz = i;
                        // best_mid = j;
                        // best_kon = k;
                    // }
                }                    
            }
        }
    }
    if (mi == INT_MAX || mx == INT_MAX) {
        printf("0 0\n");
    } else {
        printf("%d %d\n", mi, mx);
        // printf("%d [%d %d %d]\n", n, best_pocz, best_mid, best_kon);
    }

    return 0;
}