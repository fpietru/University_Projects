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

// zdegenerowana trojka to taka, ktorej poczatek jest wiekszy od konca
// uzywam ich do reprezentacji podzbiorow pustych
static void degeneruj_trojke(trojka *a) {
    *a = (trojka){1, -1, 0};
}

static bool czy_zdegenerowana_trojka(trojka a) {
    return (a.poczatek > a.koniec);
}

// true <=> a < b
// trojki sa sortowane w pierwszej kolejnosci po reszcie, potem po poczatku, a w ostatniej kolejnosci po koncu
static bool czy_mniejsza_trojka(trojka a, trojka b) {
    if (a.reszta < b.reszta) {
        return true;
    } else if (a.reszta > b.reszta) {
        return false;
    } else {
        if (a.poczatek == b.poczatek) {
            return (a.koniec < b.koniec);
        }
        return (a.poczatek < b.poczatek);
    }
}

// true <=> a \subseteq b
static bool czy_zawarta_trojka(trojka a, trojka b) {
    return (b.poczatek <= a.poczatek && a.koniec <= b.koniec);
}


// Definicja: wlasciwe przeciecie = istnieje element x ktory nalezy do trojki a oraz trojki b
// Definicja: przeciecie = wlasciwe przeciecie LUB trojka a i trojka b sa "obok siebie" tzn. a.koniec + GLOBAL_Q == b.poczatek (lub na odwrot) 
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

void zwolnij_pamiec(zbior_ary *A) {
    if (A->tablica != NULL) {
        free(A->tablica);
        A->tablica = NULL;
    }
    A->rozmiar = 0;
}

zbior_ary ciag_arytmetyczny(int a, int q, int b) {
    GLOBAL_q = q;
    zbior_ary A = nowy_zbior(1);
    A.tablica[0] = nowa_trojka(a, b, modulo_q(a));
    return A;
}

static bool czy_pusty(zbior_ary A) {
    return (A.tablica == NULL || (A.rozmiar == 1 && czy_zdegenerowana_trojka(A.tablica[0])));
}

zbior_ary singleton(int a) {
    return ciag_arytmetyczny(a, GLOBAL_q, a);
}

// binsearch po uporzadkowanej tablicy trojek w A
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
    // x nalezy do A <=> jest wlasciwe przeciecie
    return (czy_jest_przeciecie(A.tablica[st], x) && (A.tablica[st].poczatek <=  x.poczatek && x.koniec <= A.tablica[st].koniec));
}

// Usuwam wszystkie zdegenerowane trojki z tablicy w zbiorze A
static void wywal_zdegenerowane(zbior_ary *A) {
    unsigned ile_niezdegenerowanych = 0;
    for (unsigned i=0; i<A->rozmiar; i++) {
        if (czy_zdegenerowana_trojka(A->tablica[i]) == 0) {
            ile_niezdegenerowanych++;
        }
    }
    // Jesli wszystkie elementy sa zdegenerowane to przeksztalcam A w zbior pusty
    if (ile_niezdegenerowanych == 0) {
        zwolnij_pamiec(A);
        zbior_ary pusty = nowy_zbior(1);
        degeneruj_trojke(&pusty.tablica[0]);
        *A = pusty;
        return;
    }
    // Wrzucam wszystkie niezdegenerowane trojki do pomocniczego zbioru B
    zbior_ary B = nowy_zbior(ile_niezdegenerowanych);
    unsigned k = 0;
    for (unsigned i=0; i<A->rozmiar; i++) {
        if (czy_zdegenerowana_trojka(A->tablica[i]) == 0) {
            B.tablica[k++] = A->tablica[i];
        }
    }
    zwolnij_pamiec(A);
    *A = B;
}

// ary(A) = minimalna liczba ciagow arytmetycznych ktore stanowia podzial zbioru A 
unsigned ary(zbior_ary A) {
    if (czy_pusty(A)) {
        return 0;
    }
    if (A.rozmiar == 1) {
        return 1;
    }
    trojka ostatnia = A.tablica[0];
    unsigned res = A.rozmiar;
    for (unsigned i=1; i<A.rozmiar; i++) {
        if (czy_jest_przeciecie(ostatnia, A.tablica[i])) { // jesli dwie kolejne trojki sie przecinaja to wystarczy jeden ciag ary. do ich opisu
            ostatnia = scal_trojki(ostatnia, A.tablica[i]);
            res--;
        }
        else {
            ostatnia = A.tablica[i];
        }
    }
    return res;
}

unsigned moc(zbior_ary A) {
    // assert(A.rozmiar == ary(A));
    unsigned res = 0;
    for (unsigned i=0; i<A.rozmiar; i++) {
        trojka a = A.tablica[i];
        if (czy_zdegenerowana_trojka(a) == 0) {
            unsigned long long odlegosc = (unsigned long long)abs(a.koniec - a.poczatek);
            unsigned long long ilosc = odlegosc / (unsigned long long)GLOBAL_q + 1;
            res += (unsigned)ilosc;
        }
    }
    return res;
}

// Funkcja sprawia, ze zachodzi: ary(A) = A.rozmiar
static void kompresja_zbioru(zbior_ary *A) {
    // wywalam smieci
    wywal_zdegenerowane(A);
    if (A->rozmiar == 1) {
        return;
    }
    zbior_ary B = nowy_zbior(ary(*A));
    B.tablica[0] = A->tablica[0];
    int k=0;
    for (unsigned i=1; i<A->rozmiar; i++) {
        trojka a = A->tablica[i];
        trojka b = B.tablica[k];
        // jesli moge scalic trojki to to robie i rezultat wrzucam do tablicy w B
        if (czy_jest_przeciecie(a, b)) {
            B.tablica[k] = scal_trojki(a, b);
        } else {
            B.tablica[++k] = a;
        }
    }
    // informacja(B);
    zwolnij_pamiec(A);
    *A = B;
}

zbior_ary suma(zbior_ary A, zbior_ary B) {
    if (czy_pusty(A)) return B;
    if (czy_pusty(B)) return A;
    
    // C to zbior ktory jest suma teoriomnogosciowa A i B
    zbior_ary C = nowy_zbior(A.rozmiar + B.rozmiar);
    // Scalam dwie posortowane tablice w jedna jak w mergesortcie
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
    
    kompresja_zbioru(&C);
    return C;
}

zbior_ary roznica(zbior_ary A, zbior_ary B) {
    if (czy_pusty(A) || czy_pusty(B)) {
        return A;
    }

    // K = pomocniczy zbior, poniewaz nie chce modyfikowac A
    zbior_ary K = nowy_zbior(A.rozmiar);
    for (unsigned i=0; i<A.rozmiar; i++) {
        K.tablica[i] = A.tablica[i];
    }

    // C = zbior na ktory trafiac beda wszystkie a_lewa
    zbior_ary C = nowy_zbior(K.rozmiar + B.rozmiar);
    unsigned i = 0, j = 0, k = 0;
    while (i < K.rozmiar && j < B.rozmiar) {
        trojka a = K.tablica[i];
        trojka b = B.tablica[j];
        
        if ((czy_zdegenerowana_trojka(a) == 0) && (czy_jest_przeciecie(a, b) == 1)) {
            if (czy_zawarta_trojka(a, b)) { // jesli a \subseteq b to a \setminus b = \varnothing => trojka a staje sie zdegenerowana
                degeneruj_trojke(&K.tablica[i]);
                a = K.tablica[i];
            } else {
                trojka a_lewa = nowa_trojka(a.poczatek, b.poczatek - GLOBAL_q, a.reszta); // lewa polowa a po odjeciu b 
                trojka a_prawa = nowa_trojka(b.koniec + GLOBAL_q, a.koniec, a.reszta); // prawa polowa a po odjeciu b

                // a_lewa docelowo trafia do tablicy w C
                if (czy_zdegenerowana_trojka(a_lewa) == 0) {
                    C.tablica[k++] = a_lewa;
                }

                // a_prawa docelowo zastepuje a w tablicy w K
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
    // tablica w D to tablica z C, ale bez zbednych zerowych trojek na koncu
    zbior_ary D = nowy_zbior(k);
    for (unsigned l=0; l<k; l++) {
        D.tablica[l] = C.tablica[l];
    }

    zwolnij_pamiec(&C);
    wywal_zdegenerowane(&K);
    zbior_ary res = suma(K, D);
    kompresja_zbioru(&res);
    return res;
}

zbior_ary iloczyn(zbior_ary A, zbior_ary B) {
    return roznica(A, roznica(A, B)); // latwe do udowodnienia na diagramie Venna
}