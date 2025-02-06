#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <random>

using namespace std;

// Klasa Oferta
class Oferta {
private:
    string nazwa;
    double cena;
    int liczba_sztuk;
public:
    Oferta(string nazwa, double cena, int liczba_sztuk);
    ~Oferta();
    string getNazwa() const;
    double getCena() const;
    int getLiczbaSztuk() const;
    void setCena(double nowaCena);
    void setLiczbaSztuk(int nowaLiczba);
    Oferta(const Oferta&) = delete;
    Oferta& operator=(const Oferta&) = delete;
};

// Klasa bazowa dla użytkowników giełdy
class Uzytkownik {
protected:
    string id;
public:
    Uzytkownik(string id);
    virtual ~Uzytkownik();
    string getId() const;
    Uzytkownik(const Uzytkownik&) = delete;
    Uzytkownik& operator=(const Uzytkownik&) = delete;
};

// Klasa Sprzedajacy
class Sprzedajacy : public Uzytkownik {
private:
    vector<Oferta*> oferty;
public:
    Sprzedajacy(string id);
    ~Sprzedajacy();
    void wystaw_oferte(string nazwa, double cena, int liczba_sztuk);
    vector<Oferta*>& getOferty();
    Sprzedajacy(const Sprzedajacy&) = delete;
    Sprzedajacy& operator=(const Sprzedajacy&) = delete;
};

// Klasa Kupujacy
class Kupujacy : public Uzytkownik {
protected:
    double budzet;
public:
    Kupujacy(string id, double budzet);
    virtual ~Kupujacy();
    virtual void kup(vector<Oferta*>& oferty, const string& nazwa) = 0;
    void zmniejszBudzet(double kwota) { budzet -= kwota; }
    double getBudzet() const { return budzet; }
};

// Konkretne typy Kupujących
class Wybredny : public Kupujacy {
public:
    Wybredny(string id, double budzet);
    ~Wybredny();
    void kup(vector<Oferta*>& oferty, const string& nazwa) override;
};

class Niezdecydowany : public Kupujacy {
public:
    Niezdecydowany(string id, double budzet);
    ~Niezdecydowany();
    void kup(vector<Oferta*>& oferty, const string& nazwa) override;
};

class Ekonomiczny : public Kupujacy {
public:
    Ekonomiczny(string id, double budzet);
    ~Ekonomiczny();
    void kup(vector<Oferta*>& oferty, const string& nazwa) override;
};

// Klasa Gielda
class Gielda {
private:
    vector<Sprzedajacy*> sprzedajacy;
    vector<Kupujacy*> kupujacy;
public:
    Gielda();
    ~Gielda();
    void zarejestruj_sprzedajacego(Sprzedajacy* s);
    void zarejestruj_kupujacego(Kupujacy* k);
    vector<Oferta*> znajdz_oferty(const string& nazwa);
    void wykonajTransakcje(Kupujacy* kupujacy, Sprzedajacy* sprzedajacy, Oferta* oferta, int ilosc);
    friend ostream& operator<<(ostream& os, const Gielda& g);
    Gielda(const Gielda&) = delete;
    Gielda& operator=(const Gielda&) = delete;
};

// Implementacja metod
Gielda::Gielda() {}
Gielda::~Gielda() {
    for (auto s : sprzedajacy) {
        for (auto o : s->getOferty()) {
            delete o;
        }
        delete s;
    }
    for (auto k : kupujacy) {
        delete k;
    }
}

Sprzedajacy::~Sprzedajacy() {
    for (auto o : oferty) {
        delete o;
    }
}

void Sprzedajacy::wystaw_oferte(string nazwa, double cena, int liczba_sztuk) {
    oferty.push_back(new Oferta(nazwa, cena, liczba_sztuk));
}

void Gielda::wykonajTransakcje(Kupujacy* kupujacy, Sprzedajacy* sprzedajacy, Oferta* oferta, int ilosc) {
    if (ilosc <= oferta->getLiczbaSztuk() && kupujacy->getBudzet() >= ilosc * oferta->getCena()) {
        kupujacy->zmniejszBudzet(ilosc * oferta->getCena());
        oferta->setLiczbaSztuk(oferta->getLiczbaSztuk() - ilosc);
    }
}

ostream& operator<<(ostream& os, const Gielda& g) {
    for (const auto& s : g.sprzedajacy) {
        for (const auto& oferta : s->getOferty()) {
            os << "Sprzedawca: " << s->getId() << " | Towar: " << oferta->getNazwa() << " | Cena: " << oferta->getCena() << " | Sztuki: " << oferta->getLiczbaSztuk() << endl;
        }
    }
    return os;
}
