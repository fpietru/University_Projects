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

int numerek(interesant *i) {
    return i->numer;
}

// przypisuje wartosci interesantowi
void ustaw_wartosci(interesant *i, int k) {
    i->po_lewo = NULL;
    i->po_prawo = NULL;
    i->przy_okienku = k;
}

// sprawdza czy okienko jest puste
bool puste(okienko *o) {
    return (o->pocz == NULL && o->kon == NULL);
}

// funkcja do debuggu
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

// dodaje interesanta i na koniec kolejki przy okienku k
void dodaj_na_koniec(interesant *i, int k) {
    okienko *o = &wektor_okienek[k];
    ustaw_wartosci(i, k);
    if (puste(o)) {
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

// wycina i z jego kolejki i laczy jego obu sasiadow ze soba
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

// usuwa pierwszego interesanta z kolejki oraz zwraca go na wynik
// przy okazji zmienia poczatek kolejki do ktorej nalezal
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
    std::cout << "ZMIANA OKIENKA\n";
    if (i->przy_okienku == k) return;
    assert(wytnij(i) != NULL);
    dodaj_na_koniec(i, k);
}

// kolejka przy okienku nr. k2 wchlania kolejke
// ktora stala przy okienku nr. k1.
// nie zmienia jej kolejnosci.
void zamkniecie_okienka(int k1, int k2) {
    okienko *o1 = &wektor_okienek[k1];
    okienko *o2 = &wektor_okienek[k2];
    if (puste(o1))
        return;
    
    if (puste(o2)) { // jak o2 puste, to bedzie calym o1
        o2->pocz = o1->pocz;
        o2->kon = o1->kon;
    } else {
        // jak nie jest puste to koniec o2 lacze z poczatkiem o1
        // trzeba rozpatrzec oba przypadki kolejnosci w o2
        // 1) kolejnosc od lewej do prawej
        if (o2->kon->po_prawo == NULL) {
            o2->kon->po_prawo = o1->pocz;
            if (o1->pocz->po_lewo == NULL) {
                o1->pocz->po_lewo = o2->kon;
            } else {
                o1->pocz->po_prawo = o2->kon;  
            }
        } else { // 2) kolejnosc od prawej do lewej
            o2->kon->po_lewo = o1->pocz;
            if (o1->pocz->po_lewo == NULL) {
                o1->pocz->po_lewo = o2->kon;
            } else {
                o1->pocz->po_prawo = o2->kon;
            }
        }
        o2->kon = o1->kon;
    }
    // czyszcze kolejke o1
    o1->pocz = NULL;
    o1->kon = NULL;
}

// przejscie po interesantach w kolejce w kolejnosci od i1 do i2 wlacznie
// uwaga: zakladam, ze po prawo lub po lewo od i1 wystepuje NULL
// wtedy poruszam sie w kierunku przeciwnym do NULL'a
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

// wycinam fragment od i1 do i2 z kolejki w ktorej sie znajduja
// ewentualnie zmieniam pocz/kon tej kolejki
std::vector<interesant*> fast_track(interesant *i1, interesant *i2) {
    if (i1 == i2) return {wytnij(i1)};
    okienko *s = (okienko*)malloc(sizeof(okienko));
    okienko *o = &wektor_okienek[i1->przy_okienku];
    s->pocz = i1;
    s->kon = i1;
    // bede rozszerzal sie s w obu kierunkach dopoki jeden koniec
    // nie bedzie i2
    while (s->pocz != i2 && s->kon != i2) {
        interesant *nast1 = s->pocz->po_lewo;
        interesant *nast2 = s->kon->po_prawo;
        if (nast1 != NULL) s->pocz = nast1;
        if (nast2 != NULL) s->kon = nast2;
    }
    interesant *l, *p;
    // pozostalo obciac s do [i1, i2] lub [i2, i1]
    // ,a nastepnie scalic ze soba najbliszych interesantow przy obu koncach
    // przez to ze do rozpatrzenia sa podobne przypadki, kod wyglada podobnie
    // ale NIE jest duplikowany
    // przypadki do rozpatrzenia:
    // 1) jesli i2 stoi na lewo od i1:
    if (s->pocz == i2) {
        s->kon = i1;
        std::swap(s->pocz, s->kon);
        l = s->kon->po_lewo;
        p = s->pocz->po_prawo;
        s->kon->po_lewo = NULL;
        s->pocz->po_prawo = NULL;
        if (o->kon == s->kon) o->kon = p;
        if (o->pocz == s->pocz) o->pocz = l;
    } else { // w przeciwnym wypadku:
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

// odwracam kolejnosc w kolejce przy okienku nr. k
void naczelnik(int k) {
    okienko *o = &wektor_okienek[k];
    std::swap(o->pocz, o->kon);
}

// zwracam wszystkich interesantow:
// najpierw po nr. okienka
// potem po kolejnosci w kolejce w ktorej stoi
std::vector<interesant*> zamkniecie_urzedu() {
    std::vector<interesant*> wynik;
    for (int i=0; i<liczba_okienek; i++) {
        okienko *o = &wektor_okienek[i];
        std::vector<interesant*> kolejka = przejscie_po_kolejce(o->pocz, o->kon);
        wynik.insert(wynik.end(), kolejka.begin(), kolejka.end());
    }
    return wynik;
}

std::string numer_str(interesant *i) {
    if (i == NULL) return "NULL";
    return std::to_string(i->numer);
}

// funkcja do debuggu
void wypisz_okienka() {
    std::cout << "----------------------------\n";
    for (int i=0; i<liczba_okienek; i++) {
        okienko o = wektor_okienek[i];
        std::cout << "Okienko nr." << i << ":\n";
        std::cout << "pocz = " << numer_str(o.pocz) << " kon = " << numer_str(o.kon) << " [\n";
        for (auto it : przejscie_po_kolejce(o.pocz, o.kon)) {
            assert(it != NULL);
            std::cout << "( "<< numer_str(it) << ", L=" << numer_str(it->po_lewo) << ", P=" << numer_str(it->po_prawo) << ", O=" << it->przy_okienku << ")\n";
        }
        std::cout << "]\n\n";
    }
    std::cout << "----------------------------\n";
}