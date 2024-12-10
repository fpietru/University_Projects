#include "kol.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

struct okienko {
    interesant *pierwszy, *ostatni;
    bool kierunek;
};
std::vector<okienko> wektor_okienek;
int liczba_okienek;
int liczba_interesantow;

void otwarcie_urzedu(int m) {
    liczba_okienek = m;
    for (int i=0; i<m; i++) {
        okienko *o = (okienko*)malloc(sizeof(okienko));
        o->pierwszy = NULL;
        o->ostatni = NULL;
        o->kierunek = 0;
        wektor_okienek.push_back(*o);
    }
}

int numerek(interesant *i) {
    return i->numer;
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
    else std::cout << numerek(i->po_prawo) << "\n"; 
}

void dodaj_na_koniec(interesant *i, int k) {
    okienko *o = &wektor_okienek[k];
    i->po_lewo = NULL;
    i->po_prawo = NULL;
    i->przy_okienku = k;
    if (o->ostatni == NULL) {
        o->pierwszy = i;
        o->ostatni = i;
        return;
    }
    if (o->kierunek == 0) {
        (o->ostatni)->po_prawo = i;
        i->po_lewo = o->ostatni;
    } else {
        (o->ostatni)->po_lewo = i;
        i->po_prawo = o->ostatni;
    }
    o->ostatni = i;
}

interesant* usun_z_poczatku(int k) {
    okienko *o = &wektor_okienek[k];
    if (o->pierwszy == NULL) {
        return NULL;
    }
    interesant *wynik;
    if (o->kierunek == 0) {
        interesant *i = o->pierwszy;
        interesant *nast = i->po_prawo;
        i->po_prawo = NULL;
        o->pierwszy = nast;
        if (nast != NULL) {
            nast->po_lewo = NULL;
        } else {
            o->ostatni = NULL;
        }
        wynik = i;
    } else {
        interesant *i = o->pierwszy;
        interesant *nast = i->po_lewo;
        i->po_lewo = NULL;
        o->pierwszy = nast;
        if (nast != NULL) {
            nast->po_prawo = NULL;
        } else {
            o->ostatni = NULL;
        }
        wynik = i;
    }
    wynik->przy_okienku = -1;
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
    interesant *l = i->po_lewo;
    interesant *p = i->po_prawo;
    if (l != NULL) {
        l->po_prawo = p;
    }
    if (p != NULL) {
        p->po_lewo = l;
    }
    okienko *o = &wektor_okienek[i->przy_okienku];
    if (o->pierwszy == i) {
        if (o->kierunek == 0)
            o->pierwszy = p;
        else o->pierwszy = l;
    }
    if (o->ostatni == i) {
        if (o->kierunek == 0)
            o->ostatni = l;
        else o->ostatni = p;
    }
    dodaj_na_koniec(i, k);
}

void zamkniecie_okienka(int k1, int k2) {
    okienko *o1 = &wektor_okienek[k1];
    okienko *o2 = &wektor_okienek[k2];
    if (o2->kierunek == 0) {

    } else {

    }
}

void wypisz_okienka() {
    for (int i=0; i<liczba_okienek; i++) {
        okienko o = wektor_okienek[i];
        std::cout << "Okienko nr." << i << ":\n";
        std::cout << "Pierwszy = ";
        std::cout << (o.pierwszy == NULL ? "NULL" : std::to_string(numerek(o.pierwszy))) << "\n";
        std::cout << "Ostatni = ";
        std::cout << (o.ostatni == NULL ? "NULL" : std::to_string(numerek(o.ostatni))) << "\n";
        interesant *it = o.pierwszy;
        while (it != NULL) {
            std::cout << numerek(it) << " ";
            //wypisz_interesanta(it);
            if (o.kierunek == 0)
                it = it->po_prawo;
            else it = it->po_lewo;
        }
        std::cout << "\n\n";
    }
}