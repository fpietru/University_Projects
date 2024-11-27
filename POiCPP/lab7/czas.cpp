#include <bits/stdc++.h>

class Czas {
private:
    int godzina;
    int minuta;
    void napraw();

public:
    Czas(int _godzina, int _minuta) : godzina(_godzina), minuta(_minuta) {
        napraw();
    };
    ~Czas() = default;
    void drukuj24() const;
    void drukuj12() const;
    Czas &dodaj(int ileGodzin, int ileMinut);
    int ile_jeszcze(const Czas &c) const;
};

void Czas::napraw() {
    while (minuta >= 60) {
        godzina++;
        minuta -= 60;
    }
    godzina %= 24;
}

void Czas::drukuj24() const {
    printf("%02d:%02d\n", godzina, minuta);
}

void Czas::drukuj12() const {
    if (godzina >= 12) {
        printf("%02d:%02d PM\n", (godzina == 12 ? godzina : godzina - 12), minuta); 
    } else {
        printf("%02d:%02d AM\n", (godzina == 0 ? godzina + 12 : godzina), minuta);
    }
}

Czas &Czas::dodaj(int ileGodzin, int ileMinut) {
    godzina += ileGodzin;
    minuta += ileMinut;
    napraw();
    return *this;
}

int Czas::ile_jeszcze(const Czas &c) const {
    int m1 = 60 * godzina + minuta;
    int m2 = 60 * c.godzina + c.minuta;
    int rm = std::max(m2 - m1, 0);
    return rm;
}

int main() {
    Czas teraz(11, 13);
    Czas koniec(11, 45);
    teraz.drukuj24();
    teraz.drukuj12();

    std::cout << teraz.ile_jeszcze(koniec) << "\n";

    return 0;
}