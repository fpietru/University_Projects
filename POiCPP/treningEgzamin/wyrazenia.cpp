#include <bits/stdc++.h>
using namespace std;
#define up unique_ptr
#define mu make_unique

class Wyrazenie {
public:
    virtual ~Wyrazenie() {};
    virtual double wartosc(double x) = 0;
    virtual void drukuj() = 0;
    virtual up<Wyrazenie> pochodna() = 0;
    virtual up<Wyrazenie> kopia() = 0;
};

class Stala : public Wyrazenie {
private:
    double wart;
public:
    Stala(double x=0) : wart(x) {};
    double wartosc(double x) override { return wart; }
    void drukuj() override { cout << wart; }
    up<Wyrazenie> pochodna() override { return mu<Stala>(0); }
    up<Wyrazenie> kopia() override { return mu<Stala>(*this); }
};

class Zmienna : public Wyrazenie {
public:
    double wartosc(double x) override { return x; }
    void drukuj() override { cout << "x"; }
    up<Wyrazenie> pochodna() override { return mu<Stala>(1); }
    up<Wyrazenie> kopia() override { return mu<Zmienna>(*this); }
};

class Operator : public Wyrazenie {
protected:
    up<Wyrazenie> lewy;
    up<Wyrazenie> prawy;
public:
    Operator(const up<Wyrazenie>& _lewy, const up<Wyrazenie>& _prawy)
        : lewy(_lewy->kopia()), prawy(_prawy->kopia()) {}

    void drukuj() override { lewy->drukuj(); drukuj_nazwe(); prawy->drukuj(); }
    virtual void drukuj_nazwe() = 0;
};

class Plus : public Operator {
public:
    Plus(const up<Wyrazenie>& _lewy, const up<Wyrazenie>& _prawy)
        : Operator(_lewy, _prawy) {}

    void drukuj_nazwe() override { cout << "+"; }
    double wartosc(double x) override { return lewy->wartosc(x) + prawy->wartosc(x); }
    up<Wyrazenie> pochodna() override { 
        return mu<Plus>(lewy->pochodna(), prawy->pochodna());
    }
    up<Wyrazenie> kopia() override { 
        return mu<Plus>(lewy->kopia(), prawy->kopia()); 
    }
};

class Razy : public Operator {
public:
    Razy(const up<Wyrazenie>& _lewy, const up<Wyrazenie>& _prawy)
        : Operator(_lewy, _prawy) {}

    void drukuj_nazwe() override { cout << "*"; }
    double wartosc(double x) override { return lewy->wartosc(x) * prawy->wartosc(x); }
    up<Wyrazenie> pochodna() override {
        return mu<Plus>(mu<Razy>(lewy->pochodna(), prawy->kopia()), 
        mu<Razy>(lewy->kopia(), prawy->pochodna()));
    }
    up<Wyrazenie> kopia() override { 
        return mu<Razy>(lewy->kopia(), prawy->kopia()); 
    }
};

class Funkcja : public Wyrazenie {
protected:
    up<Wyrazenie> arg;
public:
    Funkcja(const up<Wyrazenie>& _arg) : arg(_arg->kopia()) {}
    void drukuj() override { drukuj_nazwe(); cout << "("; arg->drukuj(); cout << ")"; }
    virtual void drukuj_nazwe() = 0;
};

class Sinus : public Funkcja {
public:
    Sinus(const up<Wyrazenie>& _arg) : Funkcja(_arg) {}
    double wartosc(double x) override { return sin(arg->wartosc(x)); }
    up<Wyrazenie> pochodna() override;
    up<Wyrazenie> kopia() override { return mu<Sinus>(arg->kopia()); }
    void drukuj_nazwe() override { cout << "sin"; }
};

class Cosinus : public Funkcja {
public:
    Cosinus(const up<Wyrazenie>& _arg) : Funkcja(_arg) {}
    double wartosc(double x) override { return cos(arg->wartosc(x)); }
    up<Wyrazenie> pochodna() override;
    up<Wyrazenie> kopia() override { return mu<Cosinus>(arg->kopia()); }
    void drukuj_nazwe() override { cout << "cos"; }
};

up<Wyrazenie> Sinus::pochodna() {
    return mu<Razy>(mu<Cosinus>(arg->kopia()), arg->pochodna());
}

up<Wyrazenie> Cosinus::pochodna() {
    return mu<Razy>(mu<Razy>(mu<Stala>(-1), mu<Sinus>(arg->kopia())),
    arg->pochodna());
}

int main() {
    up<Wyrazenie> wyr1 = mu<Sinus>(mu<Zmienna>());
    wyr1->drukuj();
    cout << "\n" << wyr1->wartosc(0) << "\n";

    up<Wyrazenie> wyr2 = mu<Cosinus>(mu<Zmienna>());
    wyr2->drukuj();
    cout << "\n" << wyr2->wartosc(0) << "\n";

    up<Wyrazenie> wyr3 = mu<Razy>(wyr1, wyr2);
    wyr3->drukuj();
    cout << "\n" << wyr3->wartosc(0) << "\n";

    up<Wyrazenie> wyr4 = wyr3->pochodna();
    wyr4->drukuj();
    cout << "\n" << wyr4->wartosc(0) << "\n";

    return 0;
}
