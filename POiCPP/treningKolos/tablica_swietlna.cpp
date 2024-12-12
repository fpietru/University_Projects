#include <iostream>
#include <stdlib.h>

using namespace std;

struct Punkt {
    int x, y;
    Punkt() = default;
    Punkt(int _x, int _y) {
        x = _x;
        y = _y;
    }
    ~Punkt() = default;
    friend ostream& operator<<(ostream& os, const Punkt& p) {
        os << "(" << p.y << "," << p.x << ")";
        return os;  
    }
};

struct Prostokat {
    Punkt p1, p2;
    Prostokat() {
        p1 = Punkt(0, 0);
        p2 = Punkt(0, 0);
    }
    Prostokat(Punkt _p1, Punkt _p2) {
        p1 = _p1;
        p2 = _p2;
    }
    ~Prostokat() = default;
    friend ostream& operator<<(ostream& os, const Prostokat& p) {
        os << "[" << p.p1 << ", " << p.p2 << "]";
        return os;
    }
};

class Pokaz {
private:
    int N; // rozmiar tablicy
    int ile; // ile mam elementow w tablicy
    Prostokat* tab; // tablica

public:
    Pokaz() = delete;
    Pokaz(int _N) {
        N = _N;
        ile = 0;
        tab = new Prostokat[N];
    }
    Pokaz(const Pokaz& p) {
       N = p.N;
       ile = p.ile;
       tab = new Prostokat[N];
       for (int i=0; i<p.N; i++)
        tab[i] = p.tab[i]; 
    }
    ~Pokaz() {
        delete[] tab;
    }
    int rozmiar() const {
        return ile;
    }
    Prostokat daj_prostokat(int i) const {
        if (i < 0 || i >= ile) {
            cout  << "ERROR: zly indeks w pokazie\n";
            exit(12);
        } else {
            return tab[i];
        }
    }
    void dodaj(const Prostokat& p) {
        if (ile >= N) {
            cout << "ERROR: przekroczono limit prostokatow w pokazie\n";
            exit(13);
        } else {
            tab[ile++] = p;
        }
    }
};

class Swiatla {
private:
    int n, m; // wysokosc, szerokosc
    bool** ekran;
public:
    Swiatla() = delete;
    Swiatla(int _n, int _m) {
        n = _n, m = _m;
        ekran = new bool*[n];
        for (int i=0; i<n; i++) {
            ekran[i] = new bool[m];
            for (int j=0; j<m; j++)
                ekran[i][j] = false;
        }
    }
    ~Swiatla() {
        for (int i=0; i<n; i++)
            delete[] ekran[i];
        delete[] ekran;
    }
    void modyfikuj(Prostokat p) {
        for (int i=p.p1.y; i<=p.p2.y; i++)
            for (int j=p.p1.x; j<=p.p2.x; j++)
                ekran[i][j] ^= 1;
    }
    void przelacz(Pokaz pok) {
        for (int i=0; i<pok.rozmiar(); i++) {
            Prostokat p = pok.daj_prostokat(i);
            modyfikuj(p);
        }
    }
    void wyswietl() const {
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++)
                cout << (ekran[i][j] ? "#" : ".");
            cout << "\n";
        }
    }
};

int main () {

    Swiatla s{10, 15};
    Pokaz p1{3};
    p1.dodaj(Prostokat(Punkt(0, 0), Punkt(14, 9)));
    p1.dodaj(Prostokat(Punkt(1, 1), Punkt(13, 8)));
    s.przelacz(p1);
    s.wyswietl();
    Pokaz p2 = Pokaz(10);
    p2.dodaj(Prostokat(Punkt(3, 2), Punkt(4, 3)));
    p2.dodaj(Prostokat(Punkt(10, 2), Punkt(11, 3)));
    p2.dodaj(Prostokat(Punkt(7, 3), Punkt(7, 5)));
    p2.dodaj(Prostokat(Punkt(4, 8), Punkt(4, 8)));
    p2.dodaj(Prostokat(Punkt(10, 8), Punkt(10, 8)));
    p2.dodaj(Prostokat(Punkt(5, 7), Punkt(9, 7)));
    s.przelacz(p2);
    cout << "\nSmutna buzia - nie zna jeszcze C++\n";
    s.wyswietl();
    Pokaz p3 = Pokaz(2);
    p3.dodaj(Prostokat(Punkt(4, 7), Punkt(10, 8)));
    s.przelacz(p3);
    cout << "\nUśmiechnięta buzia - po poznaniu C++\n";
    s.wyswietl();
 
    return 0;
}