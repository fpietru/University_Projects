/*
    Autor: Franciszek Pietrusiak
*/
package tablice;

import tablice.wyjatki.*;

public class Skalar extends Tablica {

    // czyt. tablice.Macierz
    private static class Wskaznik {
        public Skalar skalar;
        public int id;

        public Wskaznik(Skalar skalar, int id) {
            this.skalar = skalar;
            this.id = id;
        }
    }

    private double wartosc;
    private int id;
    private Wskaznik wskaznik;

    public Skalar(double wartosc) {
        super(0);
        this.wartosc = wartosc;
        // czyt. tablice.Macierz
        this.id = 0;
        this.wskaznik = new Wskaznik(this, id);
    }

    @Override
    public Skalar suma(Skalar s) {
        return new Skalar(daj() + s.daj());
    }

    @Override
    public Wektor suma(Wektor w) {
        return w.suma(this);
    }

    @Override
    public Macierz suma(Macierz m) {
        return m.suma(this);
    }

    @Override
    public void dodaj(Skalar s) {
        ustaw(daj() + s.daj());
    }

    @Override
    public void dodaj(Wektor w) {
        throw new NiezgodnoscRozmiarow("Wynik (skalar + wektor) nie jest skalarem.");
    }

    @Override
    public void dodaj(Macierz m) {
        throw new NiezgodnoscRozmiarow("Wynik (skalar + macierz) nie jest skalarem.");
    }

    @Override
    public Skalar iloczyn(Skalar s) {
        return new Skalar(daj() * s.daj());
    }

    @Override
    public Wektor iloczyn(Wektor w) {
        return w.iloczyn(this);
    }

    @Override
    public Macierz iloczyn(Macierz m) {
        return m.iloczyn(this);
    }

    @Override
    public void przemnoz(Skalar s) {
        ustaw(daj() * s.daj());
    }

    @Override
    public void przemnoz(Wektor w) {
        throw new NiezgodnoscRozmiarow("Wynik (skalar * wektor) nie jest skalarem.");
    }

    @Override
    public void przemnoz(Macierz m) {
        throw new NiezgodnoscRozmiarow("Wynik (skalar * macierz) nie jest skalarem.");
    }

    @Override
    public Skalar negacja() {
        return new Skalar(-daj());
    }

    @Override
    public void zaneguj() {
        ustaw(daj() * -1.0);
    }

    @Override
    public void przypisz(Skalar s) {
        ustaw(s.daj());
    }

    @Override
    public void przypisz(Wektor w) {
        throw new NiezgodnoscRozmiarow("Nie mozna przypisac wektora skalarowi.");
    }

    @Override
    public void przypisz(Macierz m) {
        throw new NiezgodnoscRozmiarow("Nie mozna przypisac macierzy skalarowi.");
    }

    @Override
    public double daj(int... indeks) throws ZlyIndeks {
        sprawdzIndeks(indeks);
        Skalar nastepny = wskaznik.skalar;
        if (nastepny == this) {
            return wartosc;
        }
        // czyt. tablice.Macierz
        // Dla skalara id=0, bo ma tylko jedna wartosc.
        int szukaneId = 0;
        int[] pozycja = nastepny.znajdzPozycje(szukaneId);
        return nastepny.daj(pozycja);
    }

    @Override
    public void ustaw(double wartosc, int... indeks) {
        sprawdzIndeks(indeks);
        Skalar nastepny = wskaznik.skalar;
        this.wartosc = wartosc;
        // czyt. tablice.Macierz
        // Dla skalara id=0, bo ma tylko jedna wartosc,
        // a pozycja jest pusta tablica.
        if (nastepny != this) {
            int szukaneId = 0;
            int[] pozycja = nastepny.znajdzPozycje(szukaneId);
            nastepny.ustaw(wartosc, pozycja);
        }
    }

    @Override
    public Skalar wycinek(int... obszar) {
        sprawdzObszar(obszar);
        Skalar wynik = kopia();
        // czyt. tablice.Macierz
        wynik.wskaznik.skalar = this;
        wynik.wskaznik.id = this.id;
        return wynik;
    }

    // czyt. tablice.Macierz
    @Override
    protected int[] znajdzPozycje(int id) {
        return new int[0];
    }

    @Override
    public int wymiar() {
        return 0;
    }

    @Override
    public int liczba_elementow() {
        return 1;
    }

    @Override
    public int[] ksztalt() {
        return new int[]{};
    }

    @Override
    protected String wypisz() {
        return "[" + daj() + "]";
    }

    @Override
    public Skalar kopia() {
        return new Skalar(daj());
    }

    @Override
    public void transponuj() {}

    @Override
    protected void sprawdzIndeks(int... indeks) {
        if (indeks.length != 0) {
            throw new ZlyIndeks("Skalar przyjmuje tylko pusty indeks");
        }
    }

    @Override
    protected void sprawdzObszar(int... obszar) {
        if (obszar.length != 0) {
            throw new NiezgodnoscRozmiarow("Skalar przyjmuje zero argumentow");
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof Skalar s)) return false;
        return (daj() == s.daj());
    }
}
