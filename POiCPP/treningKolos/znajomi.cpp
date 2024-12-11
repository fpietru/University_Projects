/*
Zadanie: "Znajomi"
Zaimplementować klasę Znajomi, której obiekty reprezentują zbiór osób (ponumerowanych 1..n).
Każda para może się znać lub nie, ale jeśli a zna b to b również zna a; każda osoba zna siebie samą.
Metody publiczne:
• bool zna(int a, int b) const – zwraca true wtedy i tylko wtedy, gdy a zna b
• void poznaj(int a, int b) – osoby a i b stają się znajomymi
• void wspolniZnajomi(int a, int b) const – wypisuje listę wspólnych znajomych a i b
• void spotkanie(int a) – wszyscy znajomi a poznają się ze sobą
• int max() const – zwraca osobę, która ma najwięcej znajomych (jeśli jest ich wiele, to którąkolwiek
z nich)
*/

#include <bits/stdc++.h>
using namespace std;

class Znajomi {
private:
    int n;
    bool **tab_zna;
public:
    Znajomi() = delete;
    Znajomi(const Znajomi& z) = delete;
    Znajomi& operator = (const Znajomi& z) = delete;
    Znajomi(Znajomi&& z) { tab_zna = z.tab_zna; n = z.n; z.tab_zna = nullptr; z.n = 0; }
    Znajomi& operator = (Znajomi&& z) { tab_zna = z.tab_zna; n = z.n; z.tab_zna = nullptr; z.n = 0; return *this; }
    Znajomi(int _n) {
        n = _n;
        tab_zna = new bool*[n];
        for (int i=0; i<n; i++) {
            tab_zna[i] = new bool[n];
            for (int j=0; j<n; j++)
                tab_zna[i][j] = (i == j);
        }
    }
    ~Znajomi() {
        for (int i=0; i<n; i++) {
            delete[] tab_zna[i];
        }
        delete[] tab_zna;
    }
    bool poprawne(int a) const;
    bool zna(int a, int b) const;
    void poznaj(int a, int b);
    void wspolniZnajomi(int a, int b) const;
    void spotkanie(int a);
    int max() const;
};

bool Znajomi::poprawne(int a) const {
    return (1 <= a && a <= n); 
}

bool Znajomi::zna(int a, int b) const {
    assert(poprawne(a) && poprawne(b));
    return tab_zna[a-1][b-1];
}

void Znajomi::poznaj(int a, int b) {
    assert(poprawne(a) && poprawne(b));
    tab_zna[a-1][b-1] = tab_zna[b-1][a-1] = true;
}

void Znajomi::wspolniZnajomi(int a, int b) const {
    assert(poprawne(a) && poprawne(b));
    for (int i=1; i<=n; i++)
        if (a != i && b != i && zna(a, i) && zna(b, i))
            cout << i << " ";
    cout << "\n";
}

void Znajomi::spotkanie(int a) {
    assert(poprawne(a));
    for (int i=1; i<=n-1; i++)
        for (int j=i+1; j<=n; j++)
            if (zna(a, i) && zna(a, j))
                poznaj(i, j);
}

int Znajomi::max() const {
    int res = -1;
    int best = 0;
    for (int i=1; i<=n; i++) {
        int ile_znajomych = 0;
        for (int j=1; j<=n; j++)
            if (i != j && zna(i, j))
                ile_znajomych++;
        if (best <= ile_znajomych) {
            res = i;
            best = ile_znajomych;
        }
    }
    return res;
}


int main () {
    Znajomi z(10);
    z.poznaj(2, 4);
    z.poznaj(2, 6);
    z.spotkanie(2);

    z.wspolniZnajomi(2, 4);
    Znajomi z1 = std::move(z);
    z1.wspolniZnajomi(2, 4);
    
    return 0;
}
