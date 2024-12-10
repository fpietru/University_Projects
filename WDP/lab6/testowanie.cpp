#include "kol.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <assert.h>

int main () {
    otwarcie_urzedu(3);
    wypisz_okienka();

    interesant *i1 = nowy_interesant(2);
    interesant *i2 = nowy_interesant(2);
    interesant *i3 = nowy_interesant(2);
    interesant *i4 = nowy_interesant(2);
    interesant *i5 = nowy_interesant(2);
    interesant *i6 = nowy_interesant(0);

    wypisz_okienka();

    std::cout << "[[" << obsluz(2)->numer << "]]\n";
    // assert(i1 == obsluz(2));

    wypisz_okienka();

    return 0;
}