/*
    Autor: Franciszek Pietrusiak
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#define LIMIT 1000006
#define LIMIT_K 4
int siec[LIMIT];
int odleglosc[LIMIT];
int najblizszy[2][LIMIT];
int odw[LIMIT];
int pocz[LIMIT_K];
int kon[LIMIT_K];
int n;

void przejscie_w_przod() {
    najblizszy[0][1] = -1;
    for (int i=2; i<=n; i++) {
        if (siec[i-1] == siec[i])
            najblizszy[0][i] = najblizszy[0][i-1];
        else {
            najblizszy[0][i] = i-1;
        }
    }
    memset(odw, 0, sizeof(odw));
    for (int i=1; i<=n; i++) {
        if (odw[siec[i]] == 0) {
            odw[siec[i]] = 1;
            for (int k=0; k<LIMIT_K; k++) {
                if (pocz[k] == 0) {
                    pocz[k] = i;
                    break;
                }
            }
        }
    }
}

void przejscie_w_tyl() {
    najblizszy[1][n] = -1;
    for (int i=n-1; i>=1; i--) {
        if (siec[i+1] == siec[i])
            najblizszy[1][i] = najblizszy[1][i+1];
        else {
            najblizszy[1][i] = i+1;
        }
    }
    memset(odw, 0, sizeof(odw));
    for (int i=n; i>=1; i--) {
        if (odw[siec[i]] == 0) {
            odw[siec[i]] = 1;
            for (int k=0; k<LIMIT_K; k++) {
                if (kon[k] == 0) {
                    kon[k] = i;
                    break;
                }
            }
        }
    }
}

int najblizsza_trojka() {
    int wyn = INT_MAX;
    for (int i=2; i<=n-1; i++) {
        int a = najblizszy[0][i];
        int b = najblizszy[1][i];
        if (a == -1 || b == -1)
            continue;
        if (siec[a] != siec[b]) {
            int d1 = odleglosc[i] - odleglosc[a];
            int d2 = odleglosc[b] - odleglosc[i];
            wyn = min(wyn, max(d1, d2));
        }
    }
    return wyn;
}

int sprawdz(int a, int b) {
    int wyn = INT_MIN;
    if (siec[a] == siec[b] || a == 0 || b == 0)
        return wyn;
    for (int i=a+1; i<=b-1; i++) {
        if (siec[i] != siec[a] && siec[i] != siec[b]) {
            int d1 = odleglosc[i] - odleglosc[a];
            int d2 = odleglosc[b] - odleglosc[i];
            wyn = max(wyn, min(d1, d2));
        }
    }
    return wyn;
}

int najdalsza_trojka() {
    int wyn = INT_MIN;
    for (int i=0; i<LIMIT_K; i++) {
        for (int j=0; j<LIMIT_K; j++) {
            wyn = max(wyn, sprawdz(pocz[i], kon[j]));
        }
    }
    return wyn;
}

int main () {
    assert(scanf("%d", &n));
    for (int i=1; i<=n; i++) {
        assert(scanf("%d %d", &siec[i], &odleglosc[i]));
    }

    przejscie_w_przod();
    przejscie_w_tyl();
    int mi = najblizsza_trojka();
    int mx = najdalsza_trojka();

    if (mi == INT_MAX || mx == INT_MAX) {
        printf("0 0\n");
    } else {
        printf("%d %d\n", mi, mx);
    }

    return 0;
}