#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#define LIMIT 1000006
int siec[LIMIT];
int odleglosc[LIMIT];
int najblizszy[2][LIMIT];
int pierwsze[LIMIT];
int ostatnie[LIMIT];
int n;

void oblicz_najblizsze_przed() {
    najblizszy[0][1] = -1;
    for (int i=2; i<=n; i++) {
        if (siec[i-1] == siec[i])
            najblizszy[0][i] = najblizszy[0][i-1];
        else {
            najblizszy[0][i] = i-1;
        }
    }
}

void oblicz_najblizsze_po() {
    najblizszy[1][n] = -1;
    for (int i=n-1; i>=1; i--) {
        if (siec[i+1] == siec[i])
            najblizszy[1][i] = najblizszy[1][i+1];
        else {
            najblizszy[1][i] = i+1;
        }        
    }
}

int najblizsza_trojka() {
    oblicz_najblizsze_przed();
    oblicz_najblizsze_po();
    int wyn = INT_MAX;
    for (int i=2; i<=n-1; i++) {
        int a = najblizszy[0][i];
        int b = najblizszy[1][i];
        if (a == -1 || b == -1)
            continue;
        if (siec[a] != siec[b]) {
            int d1 = odleglosc[i] - odleglosc[a];
            int d2 = odleglosc[b] - odleglosc[i];
            // printf("%d %d %d %d %d\n", i, a, b, d1, d2);
            wyn = min(wyn, max(d1, d2));
        }
    }
    return wyn;
}

int sprawdz(int pocz, int kon) {
    int wyn = INT_MIN;
    for (int i=pocz+1; i<=kon-1; i++) {
        if (siec[i] != siec[pocz] && siec[i] != siec[kon]) {
            int d1 = odleglosc[i] - odleglosc[pocz];
            int d2 = odleglosc[kon] - odleglosc[i];
            wyn = max(wyn, min(d1, d2));
        }
    }
    return wyn;
}

int najdalsza_trojka() {
    for (int i=1; i<=n; i++)
        if (pierwsze[siec[i]] == 0)
            pierwsze[siec[i]] = i;

    for (int i=n; i>=n; i--)
        if (ostatnie[siec[i]] == 0)
            ostatnie[siec[i]] = i;
    
}

int main () {
    assert(scanf("%d", &n));
    for (int i=1; i<=n; i++) {
        assert(scanf("%d %d", &siec[i], &odleglosc[i]));
    }

    int mi = najblizsza_trojka();
    int mx = najdalsza_trojka();

    if (mi == INT_MAX || mx == INT_MAX) {
        printf("0 0\n");
    } else {
        printf("%d %d\n", mi, mx);
    }

    return 0;
}