package tablice;

import wyjatki.ZlyWymiar;
import wyjatki.ZlyIndeks;
import wyjatki.ZlyObszar;

public class Skalar extends Tablica {
    private double wartosc;

    public Skalar(double wartosc) {
        super(0);
        this.wartosc = wartosc;
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
        throw new ZlyWymiar("Wynik (skalar + wektor) nie jest skalarem.");
    }

    @Override
    public void dodaj(Macierz m) {
        throw new ZlyWymiar("Wynik (skalar + macierz) nie jest skalarem.");
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
        throw new ZlyWymiar("Wynik (skalar * wektor) nie jest skalarem.");
    }

    @Override
    public void przemnoz(Macierz m) {
        throw new ZlyWymiar("Wynik (skalar * macierz) nie jest skalarem.");
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
        throw new ZlyWymiar("Nie mozna przypisac wektora skalarowi.");
    }

    @Override
    public void przypisz(Macierz m) {
        throw new ZlyWymiar("Nie mozna przypisac macierzy skalarowi.");
    }

    @Override
    public double daj(int... indeks) throws ZlyIndeks {
        sprawdzIndeks(indeks);
        return wartosc;
    }

    @Override
    public void ustaw(double wartosc, int... indeks) {
        sprawdzIndeks(indeks);
        this.wartosc = wartosc;
    }

    @Override
    public Skalar wycinek(int... obszar) {
        sprawdzObszar(obszar);
        return this;
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
            throw new ZlyObszar("Skalar przyjmuje zero argumentow");
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof Skalar s)) return false;
        return (daj() == s.daj());
    }
}
