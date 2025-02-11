/*
    Autor: Franciszek Pietrusiak
    Uwagi: Kod przetestowany w Valgrind
*/
#include <bits/stdc++.h>
using namespace std;
#define sp shared_ptr
#define ms make_shared

class Wyrazenie {
public:
    Wyrazenie() = default;
    Wyrazenie(const Wyrazenie&) = delete;
    Wyrazenie(Wyrazenie&&) = default;
    Wyrazenie& operator=(const Wyrazenie&) = delete;
    Wyrazenie& operator=(Wyrazenie&&) = default;
    virtual string wartosciuj() const = 0;
    virtual optional<string> niewartosciuj() const = 0;
    virtual string wypisz() const= 0;
    virtual sp<Wyrazenie> kopia() = 0;
};
vector<string> wartosc_zmiennej(26);
vector<bool> inicjalizowana(26);

ostream& operator<<(ostream& os, const Wyrazenie& w) {
    return os << w.wypisz();
}

class Stala : public Wyrazenie {
private:
    string tekst;
public:
    Stala(string t="") : tekst(t) {}
    string wartosciuj() const override { return tekst; }
    optional<string> niewartosciuj() const override { return tekst; }
    string wypisz() const override { return "\"" + tekst + "\""; }
    sp<Wyrazenie> kopia() override { return ms<Stala>(tekst); }
};

class Zmienna : public Wyrazenie {
private:
    char symbol;
public:
    Zmienna(char s='a', string tekst="") : symbol(s) {
        try {
            if ('a' <= symbol && symbol <= 'z') {                
                int idx = symbol - 'a';
                if (tekst != "") {
                    wartosc_zmiennej[idx] = tekst;
                    inicjalizowana[idx] = true;
                }
            } else throw(symbol);
        } catch (char sym) {
            cerr << "ERROR: Nieprawidlowa nazwa zmiennej: " << sym << "\n";
            exit(1);
        }
    }
    string wartosciuj() const override {
        try {
            if (inicjalizowana[symbol-'a'])
                return wartosc_zmiennej[symbol-'a'];
            else throw 1;
        } catch (...) {
            cerr << "ERROR: Niezainicjalizowana zmienna: " << symbol << "\n";
            exit(1);
        }
        return "";
    }
    optional<string> niewartosciuj() const override {
        return nullopt;
    }
    string wypisz() const override { string s(1, symbol); return s; }
    sp<Wyrazenie> kopia() override { return ms<Zmienna>(symbol, wartosc_zmiennej[symbol-'a']); }
};

class Operator_jednoarg : public Wyrazenie {
protected:
    sp<Wyrazenie> argument;
public:
    Operator_jednoarg(const sp<Wyrazenie> &_argument)
        : argument(_argument->kopia()) {}
    optional<string> niewartosciuj() const override {
        if (argument->niewartosciuj().has_value()) {
            return wartosciuj();            
        } else return nullopt;
    }
};

class Upper : public Operator_jednoarg {
public:
    Upper(const sp<Wyrazenie>& _argument)
        : Operator_jednoarg(_argument) {}
    string wartosciuj() const override {
        string s = argument->wartosciuj();
        for (int i=0; i<(int)s.size(); i++)
            s[i] = toupper(s[i]);
        return s;
    }
    string wypisz() const override {
        return "^" + argument->wypisz();
    }
    sp<Wyrazenie> kopia() override {
        return ms<Upper>(argument->kopia());
    }
};

class Lower : public Operator_jednoarg {
public:
    Lower(const sp<Wyrazenie>& _argument)
        : Operator_jednoarg(_argument) {}
    string wartosciuj() const override {
        string s = argument->wartosciuj();
        for (int i=0; i<(int)s.size(); i++)
            s[i] = tolower(s[i]);
        return s;
    }
    string wypisz() const override {
        return "_" + argument->wypisz();
    }
    sp<Wyrazenie> kopia() override {
        return ms<Lower>(argument->kopia());
    }    
};

class Licz : public Operator_jednoarg {
public:
    Licz(const sp<Wyrazenie>& _argument)
        : Operator_jednoarg(_argument) {}
    string wartosciuj() const override {
        string s = argument->wartosciuj();
        return to_string(s.size());
    }
    string wypisz() const override {
        return "#" + argument->wypisz();
    }
    sp<Wyrazenie> kopia() override {
        return ms<Licz>(argument->kopia());
    }
};

class Operator_dwuarg : public Wyrazenie {
protected:
    sp<Wyrazenie> lewy, prawy;
public:
    Operator_dwuarg(const sp<Wyrazenie>& _lewy, const sp<Wyrazenie>& _prawy)
        : lewy(_lewy->kopia()), prawy(_prawy->kopia()) {}
    optional<string> niewartosciuj() const override {
        if (lewy->niewartosciuj().has_value() && prawy->niewartosciuj().has_value()) {
            return wartosciuj();
        } else return nullopt;
    }
};

class Scal : public Operator_dwuarg {
public:
    Scal(const sp<Wyrazenie>& _lewy, const sp<Wyrazenie>& _prawy)
        : Operator_dwuarg(_lewy, _prawy) {}
    string wartosciuj() const override {
        string a = lewy->wartosciuj();
        string b = prawy->wartosciuj();
        return a + b;
    }
    string wypisz() const override {
        return "(" + lewy->wypisz() + "&" + prawy->wypisz() + ")";
    }
    sp<Wyrazenie> kopia() override {
        return ms<Scal>(lewy->kopia(), prawy->kopia());
    }
};

class Mask : public Operator_dwuarg {
public:
    Mask(const sp<Wyrazenie>& _lewy, const sp<Wyrazenie>& _prawy)
        : Operator_dwuarg(_lewy, _prawy) {}
    string wartosciuj() const override {
        string a = lewy->wartosciuj();
        string b = prawy->wartosciuj();
        string res = "";
        int n = a.size(), m = b.size();
        for (int i=0; i<n; i++)
            if (b[i%m] == '*') res += a[i];
        return res;
    }
    string wypisz() const override {
        return + "(" + lewy->wypisz() + "*" + prawy->wypisz() + ")";
    }
    sp<Wyrazenie> kopia() override {
        return ms<Mask>(lewy->kopia(), prawy->kopia());
    }
};

class Przeplot : public Operator_dwuarg {
public:
    Przeplot(const sp<Wyrazenie>& _lewy, const sp<Wyrazenie>& _prawy)
        : Operator_dwuarg(_lewy, _prawy) {}
    string wartosciuj() const override {
        string a = lewy->wartosciuj();
        string b = prawy->wartosciuj();
        string res = "";
        int n = a.size(), m = b.size();
        int i = 0, j = 0, k = 0;
        while ((i < n) && (j < m)) {
            if ((++k)&1) res += a[i++];
            else res += b[j++]; 
        }
        while (i < n) res += a[i++];
        while (j < m) res += b[j++];
        return res;
    }
    string wypisz() const override {
        return "(" + lewy->wypisz() + "@" + prawy->wypisz() + ")";
    }
    sp<Wyrazenie> kopia() override {
        return ms<Przeplot>(lewy->kopia(), prawy->kopia());
    }  
};

void info(const sp<Wyrazenie>& w) {
    cout << "test dla " << *w << "\n";
    cout << " - wynik z wartosciowaniem: " << w->wartosciuj() << "\n";
    cout << " - wynik bez wartosciowania: ";
    if (w->niewartosciuj().has_value())
        cout << w->niewartosciuj().value();
    cout << "\n\n";  
}

int main () {

    sp<Wyrazenie> s1 = ms<Stala>("C+o yhn hsi h usin");
    sp<Wyrazenie> s2 = ms<Stala>("+ rPto?Ti steqeto!");
    sp<Wyrazenie> z1 = ms<Zmienna>('z');

    info(z1);

    sp<Wyrazenie> w1 = ms<Przeplot>(s1, z1);
    info(w1);

    return 0;
}