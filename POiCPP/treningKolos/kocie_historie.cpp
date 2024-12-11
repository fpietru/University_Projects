#include <bits/stdc++.h>
using namespace std;

enum kierunek { gora, dol, lewo, prawo };
class Kot;

class Podworko {
private:
    string nazwa;
    int n, m;
    Kot*** tab;
    
public:
    Podworko(string, int, int);
    Podworko(Podworko&) = delete;
    ~Podworko();
    bool poprawne(int, int) const;
    Kot* wlasciciel(int, int) const;
    Kot* jaki_kot(int, int) const;
    string jaka_nazwa() const;
    int jakie_n() const;
    int jakie_m() const;
    void wypisz() const;
    void ustaw_kota(Kot*);
};

class Kot {
private:
    string imie;
    Podworko& p;
    int i, j;

public:
    Kot(string, Podworko&, int, int);
    Kot(Kot&) = delete;
    ~Kot() = default;
    string jakie_imie() const;
    int poz_OY() const;
    int poz_OX() const;
    bool walka() const;
    bool idz(kierunek);
};

// ------------ Podworko --------------

Podworko::Podworko(string _nazwa, int _n, int _m) : nazwa(_nazwa), n(_n), m(_m) {
    tab = new Kot**[n];
    for (int i=0; i<n; i++) {
        tab[i] = new Kot*[m];
        for (int j=0; j<m; j++)
            tab[i][j] = nullptr;
    }
}

Podworko::~Podworko() {
    for (int i = 0; i < n; i++)
        delete[] tab[i];
    delete[] tab;
}

bool Podworko::poprawne(int i, int j) const {
    bool OY = (0 <= i && i <= n-1);
    bool OX = (0 <= j && j <= m-1);
    return OY && OX;
}

string Podworko::jaka_nazwa() const {
    return nazwa;
}

int Podworko::jakie_n() const {
    return n;
}

int Podworko::jakie_m() const {
    return m;
}

Kot* Podworko::wlasciciel(int i, int j) const {
    if (!poprawne(i, j)) return nullptr;
    return tab[i][j];
}

Kot* Podworko::jaki_kot(int i, int j) const {
    if (!poprawne(i, j) || tab[i][j] == nullptr)
        return nullptr;
    Kot *k = tab[i][j];
    if (i == k->poz_OY() && j == k->poz_OX())
        return k;
    else return nullptr;
}

ostream& operator<<(ostream& os, const Podworko& p){
    os << "[" << p.jaka_nazwa() << ", " << p.jakie_n() << ", " << p.jakie_m() << ": " << endl;
	for (int i=0; i<p.jakie_n(); i++){
        for (int j=0; j<p.jakie_m(); j++){
            Kot *kot = p.wlasciciel(i, j);
            if(kot != nullptr){
                os << setw(8) << kot->jakie_imie();
                if(kot == p.jaki_kot(i,j))
                    os << "*";
                else
                    os << " ";
            }    
            else // pole niczyje    
                os << setw(9) << ".";
        }    
        os << endl;
    }
    os << "]";

    return os;
}

void Podworko::ustaw_kota(Kot* k) {
    int i = k->poz_OY();
    int j = k->poz_OX();
    if (k == nullptr || !poprawne(i, j)) return;
    tab[i][j] = k;
}

// ------------------------------------
// -------------- Kot -----------------

Kot::Kot(string _imie, Podworko& _p, int _i, int _j) : imie(_imie), p(_p), i(_i), j(_j) {
    p.ustaw_kota(this);
}

string Kot::jakie_imie() const {
    return imie;
}

int Kot::poz_OY() const {
    return i;
}

int Kot::poz_OX() const {
    return j;
}

bool Kot::walka() const {
    bool wygrywa = (rand() % 2); // oczywiscie ze rzucaja moneta
    return wygrywa;
}

bool Kot::idz(kierunek k) {
    int ni = i, nj = j;
    switch (k) {
        case gora:
            ni--;
            break;
        case dol:
            ni++;
            break;
        case lewo:
            nj--;
            break;
        case prawo:
            nj++;
            break;
    }
    if (!p.poprawne(ni, nj)) {
        return false;
    } else {
        Kot* w = p.wlasciciel(ni, nj);
        Kot* kot = p.jaki_kot(ni, nj);
        if (w == nullptr) {
            cout << imie << " idzie do pustego pola\n";
            i = ni, j = nj;
            p.ustaw_kota(this);
            return true;
        } else if (kot == nullptr) {
            if (walka() == true) {
                cout << imie << " wygrywa z " << w->jakie_imie() << "\n";
                i = ni, j = nj;
                p.ustaw_kota(this);
                return true;
            } else {
                cout << w->jakie_imie() << " wygrywa z " << imie << "\n";
                return false;
            }
        } else {
            cout << imie << " oraz " << kot->jakie_imie() << " stoja obok siebie\n";
            return false;
        }
    }
}

// ------------------------------------

int main () {

    cout << "Kocie historie - klasówka 22 XII 2022" << endl;
    Podworko p{"Banacha 2", 8, 6};
    Kot k1{"Zofia", p, 0, 0};
    Kot k2{"Herman", p, 5, 5};
    Kot k3{"Gienek", p, 7, 5};

    k1.idz(kierunek::prawo);
    k1.idz(kierunek::prawo);
    k1.idz(kierunek::prawo);
    k2.idz(kierunek::gora);
    k2.idz(kierunek::gora);
    k2.idz(kierunek::lewo);
    k2.idz(kierunek::lewo);
    k3.idz(kierunek::gora);
    k3.idz(kierunek::gora);
    k3.idz(kierunek::gora);
    k3.idz(kierunek::lewo);
    k3.idz(kierunek::lewo);
    k3.idz(kierunek::gora);

    cout << p << "\n";

    return 0;
}