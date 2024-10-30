// Autor: Franciszek Pietrusiak
#include "zbior_ary.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NDEBUG // wylacza asserty
#define max(a, b) ((a) >= (b) ? (a) : (b))
#define min(a, b) ((a) <= (b) ? (a) : (b))
static int GLOBAL_q;

static int modulo_q(int a) {
    int res = a % GLOBAL_q;
    if (res < 0) {
        res += GLOBAL_q;
    }
    return res;
}

static trojka nowa_trojka(int pocz, int kon, int reszt) {
    return (trojka){pocz, kon, reszt};
}

static void swap_trojek(trojka *a, trojka *b) {
    trojka tmp = *a;
    *a = *b;
    *b = tmp;
}

static void degeneruj_trojke(trojka *a) {
    *a = (trojka){1, -1, 0};
}

static bool czy_zdegenerowana_trojka(trojka a) {
    return (a.poczatek > a.koniec);
}


// q = 5
// [20, 25, 0] < [1, 6, 1]
// [0, 30, 0] > [20, 25, 0]

// true <=> a < b
static bool czy_mniejsza_trojka(trojka a, trojka b) {
    if (a.reszta < b.reszta) {
        return true;
    } else if (a.reszta > b.reszta) {
        return false;
    } else {
        if (a.koniec == b.koniec) {
            return (a.poczatek < b.poczatek);
        }
        return (a.koniec < b.koniec);
    }
}

// true <=> a \subseteq b
static bool czy_zawarta_trojka(trojka a, trojka b) {
    return (b.poczatek <= a.poczatek && a.koniec <= b.koniec);
}

static bool czy_jest_przeciecie(trojka a, trojka b) {
    if (a.reszta != b.reszta) {
        return false;
    } else {
        if (czy_mniejsza_trojka(b, a)) {
            swap_trojek(&a, &b);
        }
        bool nachodzi_z_lewej = (a.poczatek <= b.poczatek && b.poczatek <= a.koniec);
        bool obok_siebie = (a.koniec + GLOBAL_q == b.poczatek);
        return (nachodzi_z_lewej || czy_zawarta_trojka(a, b) || obok_siebie);
    }
}

static trojka scal_trojki(trojka a, trojka b) {
    assert(czy_jest_przeciecie(a, b));
    return nowa_trojka(min(a.poczatek, b.poczatek), max(a.koniec, b.koniec), a.reszta);
}

static zbior_ary nowy_zbior(unsigned rozm) {
    zbior_ary A;
    A.rozmiar = rozm;
    A.tablica = (trojka*)malloc(rozm * sizeof(trojka));
    return A;
}

zbior_ary ciag_arytmetyczny(int a, int q, int b) {
    GLOBAL_q = q;
    zbior_ary A = nowy_zbior(1);
    A.tablica[0] = nowa_trojka(a, b, modulo_q(a));
    return A;
}

static bool czy_pusty(zbior_ary A) {
    return (A.rozmiar == 1 && czy_zdegenerowana_trojka(A.tablica[0]));
}

zbior_ary singleton(int a) {
    return ciag_arytmetyczny(a, GLOBAL_q, a);
}

bool nalezy(zbior_ary A, int b) {
    if (czy_pusty(A)) {
        return false;
    }
    trojka x = nowa_trojka(b, b, modulo_q(b));
    unsigned st = 0, ed = A.rozmiar - 1;
    while (st < ed) {
        unsigned md = (st + ed) / 2;
        if (czy_jest_przeciecie(A.tablica[md], x) && (A.tablica[md].poczatek <=  x.poczatek && x.koniec <= A.tablica[md].koniec)) {
            return true;
        } else if (czy_mniejsza_trojka(A.tablica[md], x)) {
            st = md + 1;
        } else {
            ed = md;
        }
    }
    return (czy_jest_przeciecie(A.tablica[st], x) && (A.tablica[st].poczatek <=  x.poczatek && x.koniec <= A.tablica[st].koniec));
}

static zbior_ary wywal_zdegenerowane(zbior_ary A) {
    unsigned ile_niezdegenerowanych = 0;
    for (unsigned i=0; i<A.rozmiar; i++) {
        if (czy_zdegenerowana_trojka(A.tablica[i]) == 0) {
            ile_niezdegenerowanych++;
        }
    }

    if (ile_niezdegenerowanych == 0) {
        zbior_ary pusty = nowy_zbior(1);
        degeneruj_trojke(&pusty.tablica[0]);
        return pusty;
    }

    zbior_ary B = nowy_zbior(ile_niezdegenerowanych);
    unsigned k = 0;
    for (unsigned i=0; i<A.rozmiar; i++) {
        if (czy_zdegenerowana_trojka(A.tablica[i]) == 0) {
            B.tablica[k++] = A.tablica[i];
        }
    }
    return B;
}

unsigned moc(zbior_ary A) {
    unsigned res = 0;
    for (unsigned i=0; i<A.rozmiar; i++) {
        trojka a = A.tablica[i];
        if (czy_zdegenerowana_trojka(a) == 0) {
            res += (unsigned)abs(a.koniec - a.poczatek) / (unsigned)GLOBAL_q + 1;
        }
    }
    return res;
}

unsigned ary(zbior_ary A) {
    if (czy_pusty(A)) {
        return 0;
    }
    if (A.rozmiar == 1) {
        return 1;
    }
    unsigned res = A.rozmiar;
    for (unsigned i=1; i<A.rozmiar; i++) {
        if (czy_jest_przeciecie(A.tablica[i-1], A.tablica[i])) {
            res--;
        }
    }
    return res;
}

static zbior_ary kompresja_zbioru(zbior_ary A) {
    A = wywal_zdegenerowane(A);
    if (A.rozmiar == 1) {
        return A;
    }
    
    zbior_ary B = nowy_zbior(ary(A));
    B.tablica[0] = A.tablica[0];
    int k=0;

    for (unsigned i=1; i<A.rozmiar; i++) {
        trojka a = A.tablica[i];
        trojka b = B.tablica[k];
        if (czy_jest_przeciecie(a, b)) {
            B.tablica[k] = scal_trojki(a, b);
        } else {
            B.tablica[++k] = a;
        }
    }
    return B;
}

zbior_ary suma(zbior_ary A, zbior_ary B) {
    if (czy_pusty(A)) return B;
    if (czy_pusty(B)) return A;

    zbior_ary C = nowy_zbior(A.rozmiar + B.rozmiar);
    unsigned i = 0, j = 0, k = 0;
    while (i < A.rozmiar && j < B.rozmiar) {
        trojka a = A.tablica[i];
        trojka b = B.tablica[j];
        if (czy_mniejsza_trojka(a, b)) {
            C.tablica[k++] = a;
            i++;
        } else {
            C.tablica[k++] = b;
            j++;
        }
    }
    while (i < A.rozmiar) {
        C.tablica[k++] = A.tablica[i++];
    }
    while (j < B.rozmiar) {
        C.tablica[k++] = B.tablica[j++];
    }
    return kompresja_zbioru(C);
}

zbior_ary roznica(zbior_ary A, zbior_ary B) {
    if (czy_pusty(A) || czy_pusty(B)) {
        return A;
    }

    zbior_ary K = nowy_zbior(A.rozmiar);
    for (unsigned i=0; i<A.rozmiar; i++) {
        K.tablica[i] = A.tablica[i];
    }

    zbior_ary C = nowy_zbior(2*K.rozmiar);
    unsigned i = 0, j = 0, k = 0;
    while (i < K.rozmiar && j < B.rozmiar) {
        trojka a = K.tablica[i];
        trojka b = B.tablica[j];
        
        if ((czy_zdegenerowana_trojka(a) == 0) && (czy_jest_przeciecie(a, b) == 1)) {
            if (czy_zawarta_trojka(a, b)) {
                degeneruj_trojke(&K.tablica[i]);
                a = K.tablica[i];
            } else {
                trojka a_lewa = nowa_trojka(a.poczatek, b.poczatek - GLOBAL_q, a.reszta);
                trojka a_prawa = nowa_trojka(b.koniec + GLOBAL_q, a.koniec, a.reszta);

                if (czy_zdegenerowana_trojka(a_lewa) == 0) {
                    C.tablica[k++] = a_lewa;
                }
                    
                if (czy_zdegenerowana_trojka(a_prawa) == 0) {
                    K.tablica[i] = a_prawa;
                } else {
                    degeneruj_trojke(&K.tablica[i]);
                    a = K.tablica[i];
                }

            }
        }
        if ((i+1 < K.rozmiar) && (czy_zdegenerowana_trojka(a) || czy_mniejsza_trojka(a, b))) {
            i++;
        } else {
            j++;
        }
    }
    zbior_ary D = nowy_zbior(k);
    for (unsigned l=0; l<k; l++) {
        D.tablica[l] = C.tablica[l];
    }

    return kompresja_zbioru(suma(wywal_zdegenerowane(K), D));
}

zbior_ary iloczyn(zbior_ary A, zbior_ary B) {
    return roznica(A, roznica(A, B));
}
