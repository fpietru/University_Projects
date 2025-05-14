package tablice;

public abstract class Tablica {
    protected int wymiar;

    // Konstruktor
    public Tablica(int wymiar) {
        this.wymiar = wymiar;
    }

    // Operacje Arytmetyczne
    public abstract Tablica suma(Tablica t);
    public abstract void dodaj(Tablica t);
    public abstract Tablica iloczyn(Tablica t);
    public abstract void przemnoz(Tablica t);
    public abstract Tablica negacja();
    public abstract void zaneguj();

    // Przypisania
    public abstract void przypisz(Tablica t);

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
    protected abstract void sprawdzWymiar(Tablica t);
    protected abstract void sprawdzIndeks(int... indeks);
    protected abstract void sprawdzObszar(int... obszar);
}
