#include <bits/stdc++.h>
using namespace std;

class Ksztalt {
public:
    virtual void oblicz_pole() = 0;
};

class Kolo :public Ksztalt {
    double r;
public:
    Kolo(double _r) {
        r = _r;
    }
    void oblicz_pole() {
        cout << "Pole kola: " << M_PI * r * r << "\n";
    }
};

class Kwadrat :public Ksztalt {
    double a; 
public:
    Kwadrat(double _a) {
        a = _a;
    }
    void oblicz_pole() {
        cout << "Pole kwadratu: " << a * a << "\n";
    }
};

int main () {
    Kolo k(1);
    Kwadrat kw(2);

    Ksztalt *wsk;
    
    wsk = &k;
    wsk->oblicz_pole();
    
    wsk = &kw;
    wsk->oblicz_pole();

    return 0;
}