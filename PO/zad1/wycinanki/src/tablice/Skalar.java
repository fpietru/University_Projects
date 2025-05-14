package tablice;

import wyjatki.ZlyWymiar;
import wyjatki.ZlyIndeks;
import wyjatki.ZlyObszar;

public class Skalar extends Tablica {
    double wartosc;

    public Skalar(double wartosc) {
        super(0);
        this.wartosc = wartosc;
    }

    @Override
    public Tablica suma(Tablica t) {
        if (wymiar < t.wymiar()) {
            return t.suma(this);
        }
        return new Skalar(wartosc + t.daj());
    }

    @Override
    public void dodaj(Tablica t) {
        sprawdzWymiar(t);
        wartosc += t.daj();
    }

    @Override
    public Tablica iloczyn(Tablica t) {
        if (wymiar < t.wymiar()) {
            return t.iloczyn(this);
        }
        return new Skalar(wartosc * t.daj());
    }

    @Override
    public void przemnoz(Tablica t) {
        sprawdzWymiar(t);
        wartosc *= t.daj();
    }

    @Override
    public Tablica negacja() {
        return new Skalar(-wartosc);
    }

    @Override
    public void zaneguj() {
        wartosc *= -1;
    }

    @Override
    public void przypisz(Tablica t) {
        sprawdzWymiar(t);
        wartosc = t.daj();
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
    public Tablica wycinek(int... obszar) {
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
        return "[" + wartosc + "]";
    }

    @Override
    public Tablica kopia() {
        return new Skalar(wartosc);
    }

    @Override
    public void transponuj() {}

    @Override
    protected void sprawdzWymiar(Tablica t) {
        if (t.wymiar != 0) {
            throw new ZlyWymiar("Argument musi byc skalarem");
        }
    }

    @Override
    protected void sprawdzIndeks(int... indeks) {
        if (indeks.length > 0) {
            throw new ZlyIndeks("Skalar przyjmuje tylko pusty indeks");
        }
    }

    @Override
    protected void sprawdzObszar(int... obszar) {
        if (obszar.length > 0) {
            throw new ZlyObszar("Skalar przyjmuje tylko pusty obszar");
        }
    }
}
