#include <bits/stdc++.h>
using namespace std;

class Punkt {
    double x,y;
    string nazwa;
public:
    Punkt(string _nazwa="S", double _x=0.0, double _y=0.0) {
        nazwa = _nazwa;
        x = _x;
        y = _y;
    }
    void wyswietl() {
        cout << nazwa << "(" << x << "," << y << ")\n";
    }
};

class Kolo :public Punkt {
    double r;
    string nazwa;
public:
    // Kolo() = default;
    Kolo(string _nk="K", string _np="S", double _x=0.0, double _y=0.0, double _r=1.0) : Punkt(_np, _x, _y) {
        nazwa = _nk;
        r = _r;
    }
    void wyswietl() {
        cout << "Kolo o nazwie: " << nazwa << "\n";
        cout << "Srodek kola: "; Punkt::wyswietl();
        cout << "Promien: " << r << "\n";
        cout << "Pole: " << M_PI * r * r << "\n";
    }

};

int main () {
    Kolo k1;
    k1.wyswietl();

    return 0;
}