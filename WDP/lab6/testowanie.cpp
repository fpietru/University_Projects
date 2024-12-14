#include "kol.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <assert.h>

int main () {
    otwarcie_urzedu(3);

    interesant *i0 = nowy_interesant(0);
    interesant *i1 = nowy_interesant(0);
    interesant *i2 = nowy_interesant(0);
    interesant *i3 = nowy_interesant(0);

    interesant *i4 = nowy_interesant(2);
    interesant *i5 = nowy_interesant(2);
    interesant *i6 = nowy_interesant(2);
    interesant *i7 = nowy_interesant(2);
    // wypisz_okienka();

    naczelnik(2);
    // naczelnik(0);

    // wypisz_okienka();

    zamkniecie_okienka(2, 0);
    wypisz_okienka();

    std::vector<interesant*> f = fast_track(i7, i7);

    wypisz_okienka();

    std::cout << "fast track:\n";
    for (auto i : f)
        std::cout << i->numer << " ";
    std::cout << "\n";

    std::vector<interesant*> v = zamkniecie_urzedu();
    std::cout << "Po zamknieciu:\n";
    for (auto i : v)
        std::cout << i->numer << " ";
    std::cout << "\n";

    return 0;
}