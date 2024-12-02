/*
    Zadanie: "Origami"
    Autor: Franciszek Pietrusiak
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

// Wystarczajaco mala liczba
#define epsilon 1e-9


// Sposob w jaki reprezentuje punkt LUB wektor w programie
typedef struct punkt {
    double x, y;
} punkt;

/*
    Kartka ma trzy postacie:
     - Domkniety prostokat:
        - postac = 'P'
        - p1 = punkt w lewym dolnym rogu prostokata
        - p2 = punkt w prawym gornym rogu prostokata
        - k = 0
     - Domkniete kolo:
        - postac = 'K'
        - p1 = srodek kola
        - p2.x = promien
        - p2.y = 0
        - k = 0
     - Zgiecie k-tej kartki:
        - postac = 'Z'
        - p1,p2 = punkty przez ktore przechodzi prosta
          wyznaczajaca zgiecie k-tej kartki. K-ta kartka jest zginana
          w ten sposob, ze czesc kartki z prawej strony prostej (patrzac
          w kierunku od p1 do p2) jest odbijana symetrycznie na lewa
          strone wzgledem tej prostej. 
        - k = nr. kartki ktora zostaje zgieta
*/
typedef struct kartka {
    char postac;
    punkt p1, p2;
    int k;
} kartka;

// Odleglosc Euklidesowa miedzy puntami a,b
double odl(punkt a, punkt b) {
    return sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0));
}

/*
    Funkcja, ktora okresla po ktorej stronie prostej
    przechodzacej przez punkty a,b znajduje sie punkt c.
    Funkcja zwraca:
     - 'L' = jesli punkt c znajduje sie po lewej stronie prostej
     - 'W' = jesli punkt c nalezy do prostej
     - 'P' = jesli punkt c znajduje sie po prawej stronie prostej
*/
char strona(punkt a, punkt b, punkt c) {
    punkt v1 = {b.x - a.x, b.y - a.y};
    punkt v2 = {c.x - a.x, c.y - a.y};
    double iloczyn_wekorowy = v1.x * v2.y - v1.y * v2.x;
    if (iloczyn_wekorowy > 0) return 'L';
    else if (fabs(iloczyn_wekorowy) < epsilon) return 'W';
    else return 'P';
}

/*
    Funkcja, ktora zwraca odbicie punktu c wzgledem prostej przechodzacej
    przez punkty a,b. W implementacji wzorowalem sie:
    https://math.stackexchange.com/questions/65503/point-reflection-over-a-line
    Znajduje sie tam dokladnie wytlumaczenie dzialania funkcji.
*/
punkt odbicie(punkt a, punkt b, punkt c) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double A = (pow(dx, 2) - pow(dy,2)) / (pow(dx, 2) + pow(dy, 2));
    double B = 2 * dx * dy / (pow(dx, 2) + pow(dy, 2));
    punkt wynik;
    wynik.x = A * (c.x - a.x) + B * (c.y - a.y) + a.x;
    wynik.y = B * (c.x - a.x) - A * (c.y - a.y) + a.y;
    return wynik;
}

/*
    Funkcja, ktora sprawdza czy punkt P nalezy do kartki K,
    ktora jest w postaci prostokata.
*/
bool w_prostokacie(punkt P, kartka K) {
    assert(K.postac == 'P');
    bool w_OX = (K.p1.x <= P.x && P.x <= K.p2.x);
    bool w_OY = (K.p1.y <= P.y && P.y <= K.p2.y);
    return (w_OX && w_OY);
}

/*
    Funkcja, ktora sprawdza czy punkt P nalezy do kartki K,
    ktora jest w postaci kola.
*/
bool w_kole(punkt P, kartka K) {
    assert(K.postac == 'K');
    double promien = K.p2.x;
    return (odl(P, K.p1) <= promien);
}

/*
    Funkcja, ktora sprawdza ile warstw kartki K 
    przebija pinezka wbita w punkcie P,
    gdzie K = tablica_kartek[nr_kartki]
*/
int ile_warstw(punkt P, int nr_kartki, kartka tablica_kartek[]) {
    kartka K = tablica_kartek[nr_kartki];

    if (K.postac == 'P') {
        return w_prostokacie(P, K);
    } else if (K.postac == 'K') {
        return w_kole(P, K);
    } else {
        /*
            Jesli K jest w postaci zgiecia k-tej kartki,
            to aby sprawdzic ile warstw przebija pinezka w punkcie P
            nalezy sprawdzic po ktorej stronie prostej zgiecia znajduje sie P.
            Wtedy: 
            1) jesli P po prawej stronie:
              - zwracamy 0
            2) jesli P nalezy do prostej zgiecia:
              - sprawdzamy ile warstw przebija pinezka w k-tej kartce PRZED zgieciem
            3) jesli P po lewej stronie:
              - nalezy odbic P wzgledem prostej zgiecia i otrzymac punkt P2
              - dla punktow P,P2 odpowiednio sprawdzic ile warstw przebija pinezka
                w k-tej kartce PRZED zgieciem
              - tak otrzymane wyniki zsumowac i zwrocic
        */
        assert(K.postac == 'Z');
        char s = strona(K.p1, K.p2, P);
        if (s == 'P') {
            return 0;
        } else if (s == 'W') {
            return ile_warstw(P, K.k, tablica_kartek);
        } else {
            punkt P2 = odbicie(K.p1, K.p2, P);
            return ile_warstw(P, K.k, tablica_kartek) + ile_warstw(P2, K.k, tablica_kartek);
        }
    }
}

// Funkcja, ktora wczytuje n kartek i wstawia je w tablice kartek
void wczytaj_kartki(kartka tablica_kartek[], int n) {
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
        tablica_kartek[i] = K;
    }
}

// Funkcja, ktora zwraca odpowiedzi do q zapytan
void odpowiedz_na_zapytania(kartka tablica_kartek[], int q) {
    for (int i=1; i<=q; i++) {
        int nr_kartki;
        punkt P;
        assert(scanf("%d %lf %lf", &nr_kartki, &P.x, &P.y));
        int wynik = ile_warstw(P, nr_kartki, tablica_kartek);
        printf("%d\n", wynik);
    }
}

int main () {
    int n, q;
    assert(scanf("%d %d", &n, &q));

    kartka *tablica_kartek = (kartka*)malloc((size_t)(n+1) * sizeof(kartka));
    wczytaj_kartki(tablica_kartek, n);    
    odpowiedz_na_zapytania(tablica_kartek, q);
    
    return 0;
}