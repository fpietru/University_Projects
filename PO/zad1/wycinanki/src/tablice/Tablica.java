package tablice;

public abstract class Tablica {
    protected int wymiar;

    // Konstruktor
    public Tablica(int wymiar) {
        this.wymiar = wymiar;
    }

    // Operacje Arytmetyczne
    public abstract Tablica suma(Skalar s);
    public abstract Tablica suma(Wektor w);
    public abstract Tablica suma(Macierz m);
    public abstract void dodaj(Skalar s);
    public abstract void dodaj(Wektor w);
    public abstract void dodaj(Macierz m);
    public abstract Tablica iloczyn(Skalar s);
    public abstract Tablica iloczyn(Wektor w);
    public abstract Tablica iloczyn(Macierz m);
    public abstract void przemnoz(Skalar s);
    public abstract void przemnoz(Wektor w);
    public abstract void przemnoz(Macierz m);
    public abstract Tablica negacja();
    public abstract void zaneguj();

    // Przypisania
    public abstract void przypisz(Skalar s);
    public abstract void przypisz(Wektor w);
    public abstract void przypisz(Macierz m);

    // Gettery i Settery
    public abstract double daj(int... indeks);
    public abstract void ustaw(double wartosc, int... indeks);

    // Wycinki
    public abstract Tablica wycinek(int... obszar);

    // Inne Operacje
    public abstract int wymiar();
    public abstract int liczba_elementow();
    public abstract int[] ksztalt();
    protected abstract String wypisz();
    @Override
    public String toString() { return wypisz(); }
    public abstract Tablica kopia();
    public abstract void transponuj();

    // Zglaszanie Wyjatkow
    protected abstract void sprawdzIndeks(int... indeks);
    protected abstract void sprawdzObszar(int... obszar);
}
