#include "kol.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <assert.h>

int main () {
    otwarcie_urzedu(2);
    interesant *i0 = nowy_interesant(0);
    
    wypisz_okienka();
    
    std::vector<interesant*> v = fast_track(i0, i0);
    
    wypisz_okienka();

    zamkniecie_urzedu();

    wypisz_okienka();

    std::vector<interesant*> koniec = zamkniecie_urzedu();
    for (auto i : koniec)
        std::cout << i->numer << "\n";

    return 0;
}