#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

struct Para {
    int st; // stopien
    double wsp; // wspolczynnik
};

class Wielomian {
private:
    int n;
    Para* tab;
public:
    Wielomian() = delete;
    Wielomian(Para* _tab, int _n);
    ~Wielomian();
    float wartosc_w(double x) const;
    Wielomian pochodna() const;
    friend ostream& operator<<(ostream& os, const Wielomian& w);
};

Wielomian::Wielomian(Para* _tab, int _n) {
    if (_n == 0) {
        n = 1;
        tab = new Para[n];
        tab[0].st = -1;
        tab[0].wsp = 0;
    } else {
        n = _n;
        tab = new Para[n];
        for (int i=0; i<n; i++) {
            tab[i].st = _tab[i].st;
            tab[i].wsp = _tab[i].wsp;
        }
    }
}

Wielomian::~Wielomian() {
    delete[] tab;
}

float Wielomian::wartosc_w(double x) const {
    double wynik = 0;
    for (int i=0; i<n; i++) {
        double w = tab[i].wsp;
        int s = tab[i].st;
        wynik += w * pow(x, s);
    }
    return wynik;
}

Wielomian Wielomian::pochodna() const {
    Para* ntab = new Para[n];
    int k = 0;
    for (int i=0; i<n; i++) {
        double w = tab[i].wsp;
        int s = tab[i].st;
        if (s >= 1) {
            ntab[k++] = {s-1, w*s};
        }
    }
    return Wielomian(ntab, k);
}

ostream& operator<<(ostream& os, const Wielomian& w) {
    for (int i=w.n-1; i>=0; i--) {
        os << w.tab[i].wsp << (w.tab[i].st > 0 ? "x^{" + to_string(w.tab[i].st) + "} " : " ");
        if (i > 0) os << "+ ";
    }
    return os;
}

int main () {
    Para tab[2] = {{1, 2}, {4, 1}};
    Wielomian w(tab, 2);

    cout << w << "\n";
    cout << w.wartosc_w(3) << "\n";

    Wielomian p = w.pochodna();
    cout << p << "\n";

    return 0;
}