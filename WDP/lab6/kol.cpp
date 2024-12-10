#include "kol.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

struct okienko {
    interesant *pocz, *kon;
};
std::vector<okienko> wektor_okienek;
int liczba_okienek;
int liczba_interesantow;

void otwarcie_urzedu(int m) {
    liczba_okienek = m;
    for (int i=0; i<m; i++) {
        okienko *o = (okienko*)malloc(sizeof(okienko));
        o->pocz = NULL;
        o->kon = NULL;
        wektor_okienek.push_back(*o);
    }
}

int numerek(interesant *i) {
    return i->numer;
}

void ustaw_wartosci(interesant *i, int k) {
    i->po_lewo = NULL;
    i->po_prawo = NULL;
    i->przy_okienku = k;
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

void wytnij(interesant *i) {
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
}

interesant* usun_z_poczatku(int k) {
    okienko *o = &wektor_okienek[k];
    interesant *nast;
    if (o->pocz == NULL) {
        return NULL;
    } else if (o->pocz == o->kon) {
        o->pocz = NULL;
        o->kon = NULL;
    } else if (o->pocz->po_lewo == NULL) {
        nast = o->pocz->po_prawo;
    } else {
        nast = o->pocz->po_lewo;     
    }
    assert(nast != NULL);
    wytnij(o->pocz);
    o->pocz = nast;
    return o->pocz;
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
    wytnij(i);
    dodaj_na_koniec(i, k);
}

void zamkniecie_okienka(int k1, int k2) {
    okienko *o1 = &wektor_okienek[k1];
    okienko *o2 = &wektor_okienek[k2];
    if (o1->pocz == NULL && o1->kon == NULL)
        return;
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
    okienko *specjalne = (okienko*)malloc(sizeof(okienko));
    specjalne->pocz = i1;
    specjalne->kon = i1;
    while (specjalne->pocz != i2 && specjalne->kon != i2) {
        interesant *nast1 = specjalne->pocz->po_lewo;
        interesant *nast2 = specjalne->kon->po_prawo;
        if (nast1 != NULL) specjalne->pocz = nast1;
        if (nast2 != NULL) specjalne->kon = nast2;
    }
    interesant *l, *p;
    if (specjalne->pocz == i2) {
        specjalne->kon = i1;
        l = i2->po_lewo;
        p = i1->po_prawo;
        std::swap(specjalne->pocz, specjalne->kon);
    }
    else {
        specjalne->pocz = i1;
        l = i1->po_lewo;
        p = i2->po_prawo;
    }
    if (l != NULL) l->po_prawo = p;
    if (p != NULL) p->po_lewo = l;
    specjalne->pocz->po_lewo = NULL;
    specjalne->kon->po_prawo = NULL;
    return przejscie_po_kolejce(specjalne->pocz, specjalne->kon);
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
        std::cout << "\n\n";
    }
}