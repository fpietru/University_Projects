/*
    Autor: Franciszek Pietrusiak
    Uwaga: To nie jest wersja ostateczna!!!
*/
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
int vis[LIMIT];
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
    if (siec[pocz] == siec[kon] || pocz == 0 || kon == 0)
        return wyn;
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
    int A_pocz = 0, A_kon = 0;
    int B_pocz = 0, B_kon = 0;
    int C_pocz = 0, C_kon = 0;
    for (int i=1; i<=n; i++) {
        if (vis[siec[i]] == 0) {
            vis[siec[i]] = 1;
            if (A_pocz == 0) {
                A_pocz = i;
            } else if (B_pocz == 0) {
                B_pocz = i;
            } else if (C_pocz == 0) {
                C_pocz = i;
            }
        }
    }
    for (int i=1; i<=n; i++) {
        vis[i] = 0;
    }
    for (int i=n; i>=1; i--) {
        if (vis[siec[i]] == 0) {
            vis[siec[i]] = 1;
            if (A_kon == 0) {
                A_kon = i;
            } else if (B_kon == 0) {
                B_kon = i;
            } else if (C_kon == 0) {
                C_kon = i;
            }
        }
    }
    int wyn = INT_MIN;

    /*printf("[%d %d]\n", A_pocz, A_kon);
    printf("[%d %d]\n", B_pocz, B_kon);
    printf("[%d %d]\n", C_pocz, C_kon); */

    wyn = max(wyn, sprawdz(A_pocz, A_kon));
    wyn = max(wyn, sprawdz(A_pocz, B_kon));
    wyn = max(wyn, sprawdz(B_pocz, A_kon));
    wyn = max(wyn, sprawdz(B_pocz, B_kon));
    wyn = max(wyn, sprawdz(A_pocz, C_kon));
    wyn = max(wyn, sprawdz(C_pocz, A_kon));
    wyn = max(wyn, sprawdz(B_pocz, C_kon));
    wyn = max(wyn, sprawdz(C_pocz, B_kon));
    wyn = max(wyn, sprawdz(C_pocz, C_kon));
    return wyn;
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