#include <bits/stdc++.h>
using namespace std;

class Zwierze {
protected:
    double wzrost;
    int ile_zebow;
    bool *zeby;
public:
    Zwierze(double w, int z) : wzrost(w), ile_zebow(z) {
        zeby = new bool[z];
        for (int i=0; i<z; i++)
            zeby[i] = true;
    }
    double daj_wzrost() const { return wzrost; }
    int daj_liczbe_zebow() const { return ile_zebow; }
    virtual void daj_glos(ostream& os) const = 0;
    virtual ~Zwierze() { delete[] zeby; } // "Każdemu zwierzęciu zęby usuwa się tak samo."
    void usun_zab(int nr) {
        if (nr < ile_zebow) zeby[nr] = false;
    }
    bool& operator[](int nr) {
        if (nr >= ile_zebow)
            throw std::out_of_range("Indeks poza zakresem");
        return zeby[nr];
    }
};

class Pies : public Zwierze {
public:
    Pies(double w = 0.8) : Zwierze(w, 42) {}
    void daj_glos(ostream &os) const override { os << "woof!"; }
};

class Kot : public Zwierze {
    double wasy;
public:
    Kot(double w = 0.6, double wa = 0.1) : Zwierze(w, 30), wasy(wa) {}
    void daj_glos(ostream &os) const override { os << "miau"; } 
};

ostream& operator<<(ostream& os, const Zwierze& zw) {
    zw.daj_glos(os);
    return os;
}

void pokaz_zeby(Zwierze* wsk) {
    for (int i=0; i<wsk->daj_liczbe_zebow(); i++) {
        cout << "zab nr." << i << ": ";
        if ((*wsk)[i]) {
            cout << "jest";
        } else {
            cout << "nie ma";
        }
        cout << "\n";
    }
}

int main () {
    Zwierze* Fucho = new Pies();
    Zwierze* Rudy = new Kot();
    cout << "Fucho, odezwij sie! " << *Fucho << "\n";
    cout << "Rudy, odezwij sie! " << *Rudy << "\n";
    
    Fucho->usun_zab(10);

    cout << "Fucho, pokaz zeby:\n";
    pokaz_zeby(Fucho);

    delete Fucho;
    delete Rudy;

    return 0;
}