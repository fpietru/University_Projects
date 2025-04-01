package ulamki;

import daty.Data;

public class Ulamek {
    private int licznik;
    private int mianownik;

    private int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }

    private void normalizuj() {
        int g = gcd(licznik, mianownik);
        licznik /= g;
        mianownik /= g;
    }

    public Ulamek(int licznik, int mianownik) {
        this.licznik = licznik;
        this.mianownik = mianownik;
        normalizuj();
    }

    @Override
    public String toString() {
        return licznik + "/" + mianownik;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) return false;
        if (obj == this) return true;
        if (!(obj instanceof Ulamek)) return false;
        Ulamek tmp = (Ulamek)obj;
        return ((licznik == tmp.licznik)
                && (mianownik == tmp.mianownik));
    }

    public boolean jestMniejszyOd(Ulamek u) {
        return (licznik* u.mianownik < u.licznik*mianownik);
    }

    public boolean jestWiekszyOd(Ulamek u) {
        return (licznik* u.mianownik > u.licznik*mianownik);
    }

    public Ulamek razy(Ulamek u) {
        return new Ulamek(licznik*u.licznik, mianownik* u.mianownik);
    }

    public Ulamek podzielPrzez(Ulamek u) {
        Ulamek u2 = new Ulamek(u.mianownik, u.licznik);
        return this.razy(u2);
    }

    public Ulamek dodaj(Ulamek u) {
        return new Ulamek(licznik*u.mianownik + u.licznik*mianownik, mianownik * u.mianownik);
    }

    public Ulamek odejmij(Ulamek u) {
        Ulamek u2 = new Ulamek(-u.licznik, u.mianownik);
        return this.dodaj(u2);
    }

}
