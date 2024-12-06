/*
    Dokonczyc
*/
#include <bits/stdc++.h>
using namespace std;

class Slowo {
public: 
    Slowo();
    Slowo(const string& _s);
    ~Slowo() = default;
    Slowo(const Slowo& s) = default;
    Slowo& operator=(const Slowo& u) = default;
    Wynik porownaj(const Slowo& strzal) const;
    void wypisz() const;
};

class Slownik {
private:

public:
    Slownik();
    Slownik(const Slownik&);
    Slownik& operator=(const Slownik&);
    ~Slownik();
    void dodaj(const string& s);
    Slownik dajSlownik();
    Slowo dajSlowo(int i) const;
    int ile_slow() const;
};

class Zagadka {
public:
    Zagadka(const Slownik&)
    Wynik strzal(const Slowo&)
    int ile_strzalow() const;
    const Slownik& daj_slownik() const;
    const Slowo& daj_strzal(int) const;
    const Wynik& daj_wynik(int) const;
};

class Wynik {
public:
    Wynik();
    Wynik(const Wynik&);
    Wynik& operator=(const Wynik&);
    ~Wynik();
    void drukuj() const;
    bool operator != (const Wynik&) const;
};

int main () {
    Slownik sl;

    sl.dodaj("żuraw");
    sl.dodaj("matka");

    Zagadka z(sl);

    Slowo zuraw("żuraw");

    Wynik w = z.strzal(zuraw);

    w.drukuj();

    Slownik& sl1 = z.dajSlownik():
    for(int i=0; i<sl1.ile_slow(); i++) {
    Slowo s = sl1.dajSlowo(i);
    bool pasuje = true;
    for(int j=0; j<z.ile_strzalow(); j++)
        if(s.porownaj(z.daj_strzal(j)) != z.daj_wynik(j))
        pasuje = false;
    if(pasuje) {
        s.wypisz();
        Wynik w1 = z.strzal(s);
        w1.drukuj();
        if(z.wygrana() || z.przegrana()) break;
        }
    }

    Slownik sl;
    sl.dodaj("żuraw");
    sl.dodaj("matka");
    Zagadka z(sl);
    Slowo zuraw("żuraw");
    Wynik w = z.strzal(zuraw);
    w.drukuj();
    Slownik& sl1 = z.dajSlownik():
    for(int i=0; i<sl1.ile_slow(); i++) {
    Slowo s = sl1.dajSlowo(i);
    bool pasuje = true;
    for(int j=0; j<z.ile_strzalow(); j++)
        if(s.porownaj(z.daj_strzal(j)) != z.daj_wynik(j))
        pasuje = false;
    if(pasuje) {
        s.wypisz();
        Wynik w1 = z.strzal(s);
        w1.drukuj();
        if(z.wygrana() || z.przegrana()) break;
        }
    }

    return 0;
}