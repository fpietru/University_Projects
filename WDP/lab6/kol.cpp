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

// L = z lewej do prawej
// P = z prawej do lewej
enum Kierunek {L, P};
struct Okienko {
    interesant *pocz, *kon;
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
    return (o->pocz->po_prawo == o->kon);
}

ostream& operator<<(ostream& os, const interesant* i) {
    os << "[" << i->numer << "] (";
    os << numerek(i->po_lewo) << ", ";
    os << numerek(i->po_prawo) << ")";
    return os;
}

void polacz(interesant *a, interesant *b) {
    if (!a && !b) return;
    // cout << "(" << a << " " << b << ")  --";
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
    // cout << "-->  (" << a << " " << b << ")\n";
}

void L_rozlacz(interesant *i) {
    i->po_lewo = NULL; 
}

void P_rozlacz(interesant *i) {
    i->po_prawo = NULL;
}

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
    rozlacz_dwa(a, c);
    polacz(a, b);
    polacz(b, c);
}

Kierunek jaki_kierunek(Okienko *o) {
    return ((o->pocz->po_lewo == NULL) ? L : P);
}

void oproznij_okienko(Okienko *o) {
    rozlacz(o->pocz);
    rozlacz(o->kon);
    polacz(o->pocz, o->kon);
}

interesant* nastepny(interesant *i, Okienko *o) {
    if (jaki_kierunek(o) == L) return i->po_prawo;
    else return i->po_lewo;
}

interesant* wczesniejszy(interesant *i, Okienko *o) {
    if (jaki_kierunek(o) == L) return i->po_lewo;
    else return i->po_prawo;
}

interesant* pierwszy(Okienko *o) {
    if (puste(o)) return NULL;
    return nastepny(o->pocz, o);
}

interesant* ostatni(Okienko *o) {
    if (puste(o)) return NULL;
    return wczesniejszy(o->kon, o);
}

// dodaje interesanta i na koniec kolejki przy okienku k
void dodaj_na_koniec(interesant *i, int k) {
    Okienko *o = &wektor_okienek[k];
    if (puste(o)) { // jesli kolejka pusta
        wstaw(o->pocz, i, o->kon);
    } else if (jaki_kierunek(o) == L) { // jesli nie, to sprawdzam kierunek
        wstaw(wczesniejszy(o->kon, o), i, o->kon);
    } else {
        wstaw(o->kon, i, wczesniejszy(o->kon, o));
    }
}

// usuwa pierwszego interesanta z kolejki oraz zwraca go na wynik
// przy okazji zmienia poczatek kolejki do ktorej nalezal
interesant* usun_z_poczatku(int k) {
    Okienko *o = &wektor_okienek[k];
    interesant *i = NULL;
    if (!puste(o)) {
        i = nastepny(o->pocz, o);
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
        // o->pocz->po_prawo = o->kon;
        // o->kon->po_lewo = o->pocz;
        polacz(o->pocz, o->kon);
        wektor_okienek.push_back(*o);
    }
}

void naczelnik(int k) {
    Okienko *o = &wektor_okienek[k];
    if (puste(o) == false)
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

void nast(interesant **i, interesant **w) {
    if (i == NULL) return;
    interesant *ni = NULL;
    if ((*i)->po_lewo != (*w)) ni = (*i)->po_lewo;
    else ni = (*i)->po_prawo;
    (*w) = (*i);
    (*i) = ni;
}

// przejscie po interesantach w kolejce w kolejnosci od i1 do i2 wlacznie
// uwaga: zakladam, ze po prawo lub po lewo od i1 wystepuje NULL
// wtedy poruszam sie w kierunku przeciwnym do NULL'a
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
            // cout << it1 << " " << it2 << "\n";
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
    for (auto i : wyn) {
        wytnij(i);
    }
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
    return wynik;
}

string numer_str(interesant *i) {
    if (i == NULL) return "NULL";
    return to_string(i->numer);
}

// funkcja do debuggu
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