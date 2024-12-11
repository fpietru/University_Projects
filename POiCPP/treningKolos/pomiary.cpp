/*
    Zadanie: "Pomiary"
*/
#include <bits/stdc++.h>
using namespace std;

class Pomiary {
private:
    double *tab;
    int rozmiar;
    int liczba_pomiarow;

public:
    Pomiary() = delete; // wylaczam konstruktor bezargumentowy
    Pomiary(int _rozmiar) {
        rozmiar = _rozmiar;
        tab = new double[rozmiar];
        liczba_pomiarow = 0;
    }
    ~Pomiary() {
        delete[] tab;
    }

    void dodaj(double wartosc);
    double srednia() const;
    double max() const;
    Pomiary& polacz_proby(const Pomiary& p);
    void drukuj() const;
};


void Pomiary::dodaj(double wartosc) {
    if (liczba_pomiarow == rozmiar) {
        cout << "Przekroczono limit pomiarow. Nie dodaje nowego pomiaru.\n";
    } else {
        tab[liczba_pomiarow++] = wartosc;
    }
}

double Pomiary::srednia() const {
    double suma = 0;
    for (int i=0; i<liczba_pomiarow; i++)
        suma += tab[i];
    return suma / liczba_pomiarow;
}

double Pomiary::max() const {
    double res = 0.0;
    for (int i=0; i<liczba_pomiarow; i++)
        res = fmax(res, tab[i]);
    return res;
}

void Pomiary::drukuj() const {
    cout << "Wartosci kolejnych pomiarow: [";
    for (int i=0; i<liczba_pomiarow; i++)
        cout << tab[i] << " ";
    cout << "]\n";
}

Pomiary& Pomiary::polacz_proby(const Pomiary& p) {
    int n_rozmiar = liczba_pomiarow + p.liczba_pomiarow;
    double *n_tab = new double[n_rozmiar];
    int k = 0;
    for (int i=0; i<liczba_pomiarow; i++) n_tab[k++] = tab[i];
    for (int i=0; i<p.liczba_pomiarow; i++) n_tab[k++] = p.tab[i];
    delete[] tab;
    tab = n_tab;
    liczba_pomiarow = n_rozmiar;
    return *this;
}

int main () {

    Pomiary p(6);
    for (int i=0; i<6; i++)
        p.dodaj((double)i);

    p.drukuj();

    Pomiary s(4);
    s.dodaj(3);
    s.dodaj(2);
    s.drukuj();

    p.polacz_proby(s);

    p.drukuj();
    cout << p.srednia() << " " << p.max() << "\n";


    return 0;
}