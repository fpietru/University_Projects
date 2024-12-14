/*
    Zadanie: "Kolejki"
    Autor: Franciszek Pietrusiak
*/
#include "kol.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

struct okienko {
    // kazde okienko ma wskaznik na poczatek i koniec kolejki
    interesant *pocz, *kon;
};
std::vector<okienko> wektor_okienek;
int liczba_okienek;
int liczba_interesantow;

void otwarcie_urzedu(int m) {
    liczba_okienek = m;
    for (int i=0; i<m; i++) {
        okienko *o = (okienko*)malloc(sizeof(okienko));
        // poczatkowo kolejka jest pusta
        o->pocz = NULL; o->kon = NULL;
        wektor_okienek.push_back(*o);
    }
}


/*


void zamkniecie_okienka(int k1, int k2) {
    Okienko *o1 = &wektor_okienek[k1];
    Okienko *o2 = &wektor_okienek[k2];
    Kierunek kier1 = jaki_kierunek(o1);
    Kierunek kier2 = jaki_kierunek(o2);
    if (puste(o1)) return;
    else if (puste(o2)) { // jak o2 puste, to bedzie calym o1
        swap(o1->pocz, o2->pocz);
        swap(o1->kon, o2->kon);
    } else { // obie kolejki niepuste
        if (kier1 == L && kier2 == L) {
            polacz(ostatni(o2), pierwszy(o1));
        } if (kier1 == L && kier2 == P) {
            pierwszy(o1)->po_lewo = ostatni(o2);
            ostatni(o2)->po_lewo = pierwszy(o1);
        } if (kier1 == P && kier2 == L) {
            pierwszy(o1)->po_prawo = ostatni(o2);
            ostatni(o2)->po_prawo = pierwszy(o1);
        } if (kier1 == P && kier2 == P) {
            polacz(pierwszy(o1), ostatni(o2));
        }
        swap(o1->kon, o2->kon);
    }
    oproznij_okienko(o1);
}






// zakladam, ze i1 jest na lewo od i2
void polacz(interesant *i1, interesant *i2) {
    if (i1 != NULL) i1->po_prawo = i2;
    if (i2 != NULL) i2->po_lewo = i1;
}


    if (i1->po_prawo == NULL) {
        i1->po_prawo = i2;
        if (i2->po_lewo == NULL)
            i2->po_lewo = i1;
        else if (i2->po_prawo == NULL)
            i2->po_prawo = i1;
        else {
            cout << "error: nie mozna polaczyc " << i2->numer << "\n"; 
            exit(1);
        }
    }
    else if (i1->po_lewo == NULL) {
        i1->po_lewo = i2;
        if (i2->po_prawo == NULL)
            i2->po_prawo = i1;
        else if (i2->po_lewo == NULL)
    }



*/


int numerek(interesant *i) {
    return i->numer;
}

// przypisuje wartosci interesantowi
void ustaw_wartosci(interesant *i, int k) {
    i->po_lewo = NULL;
    i->po_prawo = NULL;
    i->przy_okienku = k;
}

bool puste(okienko *o) {
    return (o->pocz == NULL && o->kon == NULL);
}

void wypisz_interesanta(interesant *i) {
    std::cout << i->numer << "\n";
    std::cout << "L: ";
    if (i->po_lewo == NULL)
        std::cout << "NULL\n";
    else std::cout << numerek(i->po_lewo) << "\n";
    std::cout << "P: ";
    if (i->po_prawo == NULL)
        std::cout << "NULL\n";
    else std::cout << numerek(i->po_prawo) << "\n\n"; 
}

void dodaj_na_koniec(interesant *i, int k) {
    okienko *o = &wektor_okienek[k];
    ustaw_wartosci(i, k);
    if (o->kon == NULL) {
        o->pocz = i;
        o->kon = i;
        return;
    } else if (o->kon->po_prawo == NULL) {
        i->po_lewo = o->kon;
        o->kon->po_prawo = i;
    } else {
        i->po_prawo = o->kon;
        o->kon->po_lewo = i;
    }
    o->kon = i;
}

interesant* wytnij(interesant *i) {
    interesant *l = i->po_lewo;
    interesant *p = i->po_prawo;
    if (l != NULL) l->po_prawo = p;
    if (p != NULL) p->po_lewo = l;
    okienko *o = &wektor_okienek[i->przy_okienku];
    if (o->pocz == i) {
        if (l != NULL) o->pocz = l;
        else o->pocz = p;
    }
    if (o->kon == i) {
        if (l != NULL) o->kon = l;
        else o->kon = p;
    }
    ustaw_wartosci(i, -1);
    return i;
}

interesant* usun_z_poczatku(int k) {
    okienko *o = &wektor_okienek[k];
    interesant *nast = NULL;
    if (puste(o)) {
        return NULL;
    } else if (o->pocz == o->kon) {
        return wytnij(o->pocz);
    } else if (o->pocz->po_prawo != NULL) {
        nast = o->pocz->po_prawo;
    } else {
        nast = o->pocz->po_lewo;
    }
    interesant *wynik = wytnij(o->pocz);
    o->pocz = nast;
    return wynik;
}

interesant* nowy_interesant(int k) {
    interesant *nowy = (interesant*)malloc(sizeof(interesant));
    nowy->numer = liczba_interesantow++;
    dodaj_na_koniec(nowy, k);
    return nowy;
}

interesant* obsluz(int k) {
    return usun_z_poczatku(k);
}

void zmiana_okienka(interesant *i, int k) {
    assert(wytnij(i) != NULL);
    dodaj_na_koniec(i, k);
}

void zamkniecie_okienka(int k1, int k2) {
    okienko *o1 = &wektor_okienek[k1];
    okienko *o2 = &wektor_okienek[k2];
    if (puste(o1))
        return;
    if (puste(o2)) {
        o2->pocz = o1->pocz;
        o2->kon = o1->kon;
    } else if (o2->pocz != NULL) {
        if (o2->kon->po_prawo == NULL) {
            o2->kon->po_prawo = o1->pocz;
            if (o1->pocz->po_lewo == NULL) {
                o1->pocz->po_lewo = o2->kon;
            } else {
                o1->pocz->po_prawo = o2->kon;  
            }
        } else {
            o2->kon->po_lewo = o1->pocz;
            if (o1->pocz->po_lewo == NULL) {
                o1->pocz->po_lewo = o2->kon;
            } else {
                o1->pocz->po_prawo = o2->kon;
            }
        }
        o2->kon = o1->kon;
    }
    o1->pocz = NULL;
    o1->kon = NULL;
}

std::vector<interesant*> przejscie_po_kolejce(interesant *i1, interesant *i2) {
    std::vector<interesant*> wynik;
    interesant *it = i1;
    if (it == NULL) return wynik;
    interesant *nast = NULL;
    if (it->po_prawo != NULL)
        nast = it->po_prawo;
    else nast = it->po_lewo;
    while (it != NULL) {
        wynik.push_back(it);
        if (it == i2) {
            break;
        }
        interesant *nast2 = NULL;
        if (nast != NULL) {
            if (nast->po_prawo != it)
                nast2 = nast->po_prawo;
            else nast2 = nast->po_lewo;
        }
        it = nast;
        nast = nast2;
    }
    return wynik;
}

std::vector<interesant*> fast_track(interesant *i1, interesant *i2) {
    okienko *s = (okienko*)malloc(sizeof(okienko));
    okienko *o = &wektor_okienek[i1->przy_okienku];
    s->pocz = i1;
    s->kon = i1;
    while (s->pocz != i2 && s->kon != i2) {
        interesant *nast1 = s->pocz->po_lewo;
        interesant *nast2 = s->kon->po_prawo;
        if (nast1 != NULL) s->pocz = nast1;
        if (nast2 != NULL) s->kon = nast2;
    }
    interesant *l, *p;
    if (s->pocz == i2) {
        s->kon = i1;
        std::swap(s->pocz, s->kon);
        l = s->kon->po_lewo;
        p = s->pocz->po_prawo;
        s->kon->po_lewo = NULL;
        s->pocz->po_prawo = NULL;
        if (o->kon == s->kon) o->kon = p;
        if (o->pocz == s->pocz) o->pocz = l;
    } else {
        s->pocz = i1;
        l = s->pocz->po_lewo;
        p = s->kon->po_prawo;
        s->kon->po_prawo = NULL;
        s->pocz->po_lewo = NULL;
        if (o->kon == s->kon) o->kon = l;
        if (o->pocz == s->pocz) o->pocz = p;
    }
    if (l != NULL) l->po_prawo = p;
    if (p != NULL) p->po_lewo = l;

    return przejscie_po_kolejce(s->pocz, s->kon);
}

void naczelnik(int k) {
    okienko *o = &wektor_okienek[k];
    std::swap(o->pocz, o->kon);
}

std::vector<interesant*> zamkniecie_urzedu() {
    std::vector<interesant*> wynik;
    for (int i=0; i<liczba_okienek; i++) {
        okienko *o = &wektor_okienek[i];
        std::vector<interesant*> kolejka = przejscie_po_kolejce(o->pocz, o->kon);
        wynik.insert(wynik.end(), kolejka.begin(), kolejka.end());
    }
    return wynik;
}

void wypisz_okienka() {
    for (int i=0; i<liczba_okienek; i++) {
        okienko o = wektor_okienek[i];
        std::cout << "Okienko nr." << i << ":\n";
        std::cout << "pocz = ";
        std::cout << (o.pocz == NULL ? "NULL" : std::to_string(numerek(o.pocz))) << "\n";
        std::cout << "kon = ";
        std::cout << (o.kon == NULL ? "NULL" : std::to_string(numerek(o.kon))) << "\n";
        for (auto it : przejscie_po_kolejce(o.pocz, o.kon)) {
            assert(it != NULL);
            std::cout << it->numer << " ";
        }
        std::cout << "\n";
    }
}