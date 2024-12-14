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

using namespace std;

struct Okienko {
    interesant *pocz, *kon;
    ~Okienko() = default;
};
vector<Okienko> wektor_okienek;
int liczba_okienek;
int liczba_interesantow;

interesant* stworz_interesanta(int x) {
    interesant *i = (interesant*)malloc(sizeof(interesant));
    i->numer = x;
    i->po_lewo = NULL;
    i->po_prawo = NULL;
    return i;
}

int numerek(interesant *i) {
    if (i == NULL) return -2;
    return i->numer;
}

bool puste(Okienko *o) {
    bool op1 = (o->pocz->po_prawo == o->kon); 
    bool op2 = (o->pocz->po_lewo == o->kon);
    return (op1 || op2);
}

// do debuggu
ostream& operator<<(ostream& os, const interesant* i) {
    os << "[" << i->numer << "] (";
    os << numerek(i->po_lewo) << ", ";
    os << numerek(i->po_prawo) << ")";
    return os;
}

// laczy interesantow a, b ze soba
void polacz(interesant *a, interesant *b) {
    if (!a && !b) return;
    assert(!a->po_lewo || !a->po_prawo);
    assert(!b->po_prawo || !b->po_lewo);
    if (!a->po_prawo && !b->po_lewo)
        a->po_prawo = b, b->po_lewo = a;
    else if (!a->po_lewo && !b->po_prawo)
        a->po_lewo = b, b->po_prawo = a;
    else if (!a->po_prawo && !b->po_prawo)
        a->po_prawo = b, b->po_prawo = a;
    else if (!a->po_lewo && !b->po_lewo)
        a->po_lewo = b, b->po_lewo = a;
}

void L_rozlacz(interesant *i) {
    i->po_lewo = NULL; 
}

void P_rozlacz(interesant *i) {
    i->po_prawo = NULL;
}

// rozlacza i od jego obu sasiedow (o ile istnieja)
void rozlacz(interesant *i) {
    interesant *a = i->po_lewo;
    interesant *b = i->po_prawo;
    if (a && a->po_lewo == i) L_rozlacz(a);
    if (a && a->po_prawo == i) P_rozlacz(a);
    if (b && b->po_lewo == i) L_rozlacz(b);
    if (b && b->po_prawo == i) P_rozlacz(b);
    L_rozlacz(i);
    P_rozlacz(i);
}

// rozlacza a,b mniedzy soba
void rozlacz_dwa(interesant *a, interesant *b) {
    assert(a); assert(b);
    if (a->po_lewo == b) L_rozlacz(a);
    if (a->po_prawo == b) P_rozlacz(a);
    if (b->po_lewo == a) L_rozlacz(b);
    if (b->po_prawo == a) P_rozlacz(b);
}

// wytnij interesanta i i polacz jego obu sasiedow ze soba
void wytnij(interesant *i) {
    if (!i) return;
    interesant *sl = i->po_lewo;
    interesant *sp = i->po_prawo;
    rozlacz(i);
    polacz(sl, sp);
}

// wstaw interesanta b po miedzy interesanta a, c
void wstaw(interesant *a, interesant *b, interesant *c) {
    assert(a); assert(c);
    rozlacz_dwa(a, c);
    polacz(a, b);
    polacz(b, c);
}

void oproznij_okienko(Okienko *o) {
    rozlacz(o->pocz);
    rozlacz(o->kon);
    polacz(o->pocz, o->kon);
}

interesant* pierwszy(Okienko *o) {
    if (puste(o)) return NULL;
    if (o->pocz->po_lewo != NULL)
        return o->pocz->po_lewo;
    return o->pocz->po_prawo;
}

interesant* ostatni(Okienko *o) {
    if (puste(o)) return NULL;
    if (o->kon->po_lewo != NULL)
        return o->kon->po_lewo;
    return o->kon->po_prawo;
}

// dodaje interesanta i na koniec kolejki przy okienku k
void dodaj_na_koniec(interesant *i, int k) {
    assert(i);
    Okienko *o = &wektor_okienek[k];
    if (puste(o)) {
        wstaw(o->pocz, i, o->kon);
    } else {
        wstaw(ostatni(o), i, o->kon);
    }
}

// usuwa pierwszego interesanta z kolejki oraz zwraca go na wynik
// przy okazji zmienia poczatek kolejki do ktorej nalezal
interesant* usun_z_poczatku(int k) {
    Okienko *o = &wektor_okienek[k];
    interesant *i = NULL;
    // cout << o->pocz << " " << o->kon << "\n";
    if (!puste(o)) {
        i = pierwszy(o);
        wytnij(i);
    }
    return i;
}

interesant* nowy_interesant(int k) {
    interesant *nowy = stworz_interesanta(liczba_interesantow++);
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

void otwarcie_urzedu(int m) {
    liczba_okienek = m;
    for (int k=0; k<m; k++) {
        Okienko *o = (Okienko*)malloc(sizeof(Okienko));
        o->pocz = stworz_interesanta(-1);
        o->kon = stworz_interesanta(-1);
        polacz(o->pocz, o->kon);
        wektor_okienek.push_back(*o);
        free(o);
    }
}

void naczelnik(int k) {
    Okienko *o = &wektor_okienek[k];
    swap(o->pocz, o->kon);
}

// kolejka przy okienku nr. k1 bez zmiany kolejnosci
// przechodzi do okienka nr. k2 
void zamkniecie_okienka(int k1, int k2) {
    Okienko *o1 = &wektor_okienek[k1];
    Okienko *o2 = &wektor_okienek[k2];
    polacz(o2->kon, o1->pocz);
    wytnij(o2->kon); wytnij(o1->pocz);
    swap(o1->kon, o2->kon);
    oproznij_okienko(o1);
}

// przesuwa i na swojego nastepnika
// p = poprzednik i 
void nast(interesant **i, interesant **p) {
    assert(i);
    interesant *ni = NULL;
    if ((*i)->po_lewo != (*p)) ni = (*i)->po_lewo;
    else ni = (*i)->po_prawo;
    if (ni != NULL) {
        (*p) = (*i);
        (*i) = ni;
    }
}

// przejscie po interesantach w kolejce w kolejnosci od i1 do i2 wlacznie
vector<interesant*> przejscie_po_kolejce(interesant *i1, interesant *i2) {
    vector<interesant*> wynik;
    interesant *it = i1;
    interesant *w = NULL;
    while (it != NULL) {
        if (it->numer != -1)
            wynik.push_back(it);
        if (it == i2) {
            break;
        }
        nast(&it, &w);
    }
    return wynik;
}

// wycinam fragment od a do b wlacznie z kolejki
vector<interesant*> fast_track(interesant *a, interesant *b) {
    vector<interesant*> wyn;
    if (a == b) {
        wyn.push_back(a);
    } else {
        interesant *it1 = a, *w1 = a->po_prawo;
        interesant *it2 = a, *w2 = a->po_lewo;
        vector<interesant*> v1 = {a}, v2 = {a};
        do {
            nast(&it1, &w1), nast(&it2, &w2);
            v1.push_back(it1);
            v2.push_back(it2);
        } while (it1 != b && it2 != b);
        if (it2 == b) {
            wyn = v2;
            v1.clear();
        } else { // it1 == b
            wyn = v1;
            v2.clear();
        }
    }
    for (auto i : wyn)
        wytnij(i);
    return wyn;
}

// zwracam wszystkich interesantow:
// najpierw po nr. okienka
// potem po kolejnosci w kolejce w ktorej stoi
vector<interesant*> zamkniecie_urzedu() {
    vector<interesant*> wynik;
    for (int i=0; i<liczba_okienek; i++) {
        Okienko *o = &wektor_okienek[i];
        vector<interesant*> kolejka = przejscie_po_kolejce(o->pocz, o->kon);
        wynik.insert(wynik.end(), kolejka.begin(), kolejka.end());
    }

    // zwolnienie pamieci!
    for (int i=0; i<liczba_okienek; i++) {
        Okienko *o = &wektor_okienek[i];
        free(o->pocz); free(o->kon);
    }
    wektor_okienek.clear();

    return wynik;
}

// funkcja do debugu
string numer_str(interesant *i) {
    if (i == NULL) return "NULL";
    return to_string(i->numer);
}

// funkcja do debugu
void wypisz_okienka() {
    cout << "----------------------------\n";
    for (int i=0; i<liczba_okienek; i++) {
        Okienko o = wektor_okienek[i];
        cout << "Okienko nr." << i << ":\n";
        for (auto it : przejscie_po_kolejce(o.pocz, o.kon)) {
            assert(it != NULL);
            cout << "( "<< numer_str(it) << ", L=" << numer_str(it->po_lewo) << ", P=" << numer_str(it->po_prawo) << ")\n";
        }
        cout << "]\n\n";
    }
    cout << "----------------------------\n";
}