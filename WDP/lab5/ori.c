#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#define epsilon 1e-9

typedef struct punkt {
    double x, y;
} punkt;

typedef struct kartka {
    char postac;
    punkt p1, p2;
    int k;
} kartka;

double odl(punkt a, punkt b) {
    return sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0));
}

double iloczyn_wektorowy(punkt a, punkt b) {
    return a.x*b.y - a.y*b.x;
}

char strona(punkt a, punkt b, punkt c) {
    punkt v1 = {b.x - a.x, b.y - a.y};
    punkt v2 = {c.x - a.x, c.y - a.y};
    double ilo = iloczyn_wektorowy(v1, v2);
    if (ilo > 0) return 'L';
    else if (fabs(ilo) < epsilon) return 'W';
    else return 'P';
}

/*
    Funkcja ktora zwraca odbicie punktu P wzgledem prostej przechodzacej
    przez punkty p1, p2. Korzystalem z:
    https://math.stackexchange.com/questions/65503/point-reflection-over-a-line
*/
punkt odbicie(punkt p1, punkt p2, punkt P) {
    punkt wynik;
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double a = (pow(dx, 2) - pow(dy,2)) / (pow(dx, 2) + pow(dy, 2));
    double b = 2 * dx * dy / (pow(dx, 2) + pow(dy, 2));
    wynik.x = a * (P.x - p1.x) + b * (P.y - p1.y) + p1.x;
    wynik.y = b * (P.x - p1.x) - a * (P.y - p1.y) + p1.y;
    return wynik;
}

bool w_prostokacie(punkt P, kartka K) {
    assert(K.postac == 'P');
    bool w_OX = (K.p1.x <= P.x && P.x <= K.p2.x);
    bool w_OY = (K.p1.y <= P.y && P.y <= K.p2.y);
    return (w_OX && w_OY);
}

bool w_kole(punkt P, kartka K) {
    assert(K.postac == 'K');
    double promien = K.p2.x;
    return (odl(P, K.p1) <= promien);
}

int ile_warstw(punkt P, int nr_kartki, kartka kartki[]) {
    kartka K = kartki[nr_kartki];

    if (K.postac == 'P') {
        return w_prostokacie(P, K);
    } else if (K.postac == 'K') {
        return w_kole(P, K);
    } else {
        assert(K.postac == 'Z');
        char s = strona(K.p1, K.p2, P);
        if (s == 'P') {
            return 0;
        } else if (s == 'W') {
            return ile_warstw(P, K.k, kartki);
        } else {
            punkt P2 = odbicie(K.p1, K.p2, P);
            return ile_warstw(P, K.k, kartki) + ile_warstw(P2, K.k, kartki);
        }
    }
}

void wczytaj_kartki(kartka kartki[], int n) {
    for (int i=1; i<=n; i++) {
        kartka K;
        K.k = 0;
        assert(scanf(" %c", &K.postac));
        if (K.postac == 'P') {
            assert(scanf("%lf %lf %lf %lf", &K.p1.x, &K.p1.y, &K.p2.x, &K.p2.y));
        } else if (K.postac == 'K') {
            assert(scanf("%lf %lf %lf", &K.p1.x, &K.p1.y, &K.p2.x));
        } else {
            assert(scanf("%d %lf %lf %lf %lf", &K.k, &K.p1.x, &K.p1.y, &K.p2.x, &K.p2.y));
        }
        kartki[i] = K;
    }
}

void odpowiedz_na_zapytania(kartka kartki[], int q) {
    for (int i=1; i<=q; i++) {
        int nr_kartki;
        punkt P;
        assert(scanf("%d %lf %lf", &nr_kartki, &P.x, &P.y));
        int wynik = ile_warstw(P, nr_kartki, kartki);
        printf("%d\n", wynik);
    }
}

int main () {
    int n, q;
    assert(scanf("%d %d", &n, &q));

    kartka *kartki = (kartka*)malloc((size_t)(n+1) * sizeof(kartka));
    wczytaj_kartki(kartki, n);    
    odpowiedz_na_zapytania(kartki, q);
    
    return 0;
}