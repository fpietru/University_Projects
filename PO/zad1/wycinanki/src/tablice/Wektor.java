/*
    Autor: Franciszek Pietrusiak
*/
package tablice;

import tablice.wyjatki.*;

public class Wektor extends Tablica {

    // czyt. tablice.Macierz
    private static class Wskaznik {
        public Wektor wektor;
        public int id;

        public Wskaznik(Wektor wektor, int id) {
            this.wektor = wektor;
            this.id = id;
        }
    }

    private double[] wartosci;
    private boolean orientacja; // false = pionowy, true = poziomy
    private int[] id;
    private Wskaznik[] wskazniki;


    public Wektor(double[] wartosci, boolean orientacja) {
        super(1);
        this.wartosci = wartosci;
        this.orientacja = orientacja;
        // czyt. tablice.Macierz
        int licznik = 0;
        id = new int[liczba_elementow()];
        wskazniki = new Wskaznik[liczba_elementow()];
        for (int i=0; i<liczba_elementow(); i++) {
            id[i] = licznik++;
            wskazniki[i] = new Wskaznik(this, id[i]);
        }
    }

    @Override
    public Wektor suma(Skalar s) {
        Wektor wynik = kopia();
        for (int i=0; i<wynik.liczba_elementow(); i++) {
            double wartosc = wynik.daj(i) + s.daj();
            wynik.ustaw(wartosc, i);
        }
        return wynik;
    }

    @Override
    public Wektor suma(Wektor w) {
        sprawdzWektor(w);
        Wektor wynik = kopia();
        for (int i=0; i<wynik.liczba_elementow(); i++) {
            double wartosc = wynik.daj(i) + w.daj(i);
            wynik.ustaw(wartosc, i);
        }
        return wynik;
    }

    @Override
    public Macierz suma(Macierz m) {
        return m.suma(this);
    }

    @Override
    public void dodaj(Skalar s) {
        for (int i=0; i<liczba_elementow(); i++) {
            double wartosc = daj(i) + s.daj();
            ustaw(wartosc, i);
        }
    }

    @Override
    public void dodaj(Wektor w) {
        sprawdzWektor(w);
        for (int i=0; i<liczba_elementow(); i++) {
            double wartosc = daj(i) + w.daj(i);
            ustaw(wartosc, i);
        }
    }

    @Override
    public void dodaj(Macierz m) {
        throw new NiezgodnoscRozmiarow("Wynik (wektor + macierz) nie jest wektorem.");
    }

    @Override
    public Wektor iloczyn(Skalar s) {
        Wektor wynik = kopia();
        for (int i=0; i<wynik.liczba_elementow(); i++) {
            double wartosc = wynik.daj(i) * s.daj();
            wynik.ustaw(wartosc, i);
        }
        return wynik;
    }

    @Override
    public Tablica iloczyn(Wektor w) {
        if (liczba_elementow() != w.liczba_elementow()) {
            throw new NiezgodnoscRozmiarow("Rozna liczba elementow");
        }
        if (orientacja() == w.orientacja()) { // iloczyn skalarny
            double wynik = 0;
            for (int i=0; i<liczba_elementow(); i++) {
                wynik += daj(i) * w.daj(i);
            }
            return new Skalar(wynik);
        } else { // iloczyn wektorowy
            int n = liczba_elementow();
            double[][] wynik;
            if (orientacja()) {
                wynik = new double[][]{{0}};
                for (int i=0; i<n; i++) {
                    wynik[0][0] += daj(i) * w.daj(i);
                }
            } else {
                wynik = new double[n][n];
                for (int i=0; i<n; i++) {
                    for (int j=0; j<n; j++) {
                        wynik[i][j] = daj(i) * w.daj(j);
                    }
                }
            }
            return new Macierz(wynik);
        }
    }

    @Override
    public Wektor iloczyn(Macierz m) {
        if (!orientacja()) {
            throw new NiezgodnoscRozmiarow("Wynik nie bedzie wektorem.");
        }
        int liczbaWierszy = m.ksztalt()[0];
        int liczbaKolumn = m.ksztalt()[1];
        if (liczba_elementow() != liczbaWierszy) {
            throw new NiezgodnoscRozmiarow("Nie mozna pomnozyc przz macierz tego ksztaltu.");
        }
        Wektor wynik = new Wektor(new double[liczbaKolumn], true);
        for (int j=0; j<liczbaKolumn; j++) {
            double wartosc = 0.0;
            for (int i=0; i<liczba_elementow(); i++) {
                wartosc += daj(i) * m.daj(i, j);
            }
            wynik.ustaw(wartosc, j);
        }
        return wynik;
    }

    @Override
    public void przemnoz(Skalar s) {
        for (int i=0; i<liczba_elementow(); i++) {
            double wartosc = daj(i) * s.daj();
            ustaw(wartosc, i);
        }
    }

    @Override
    public void przemnoz(Wektor w) {
        throw new NiezgodnoscRozmiarow("Wynikiem mnozenia dwoch wektorow nie jest wektor.");
    }

    @Override
    public void przemnoz(Macierz m) {
        throw new NiezgodnoscRozmiarow("Wynikiem (wektor * macierz) nie jest jest wektor.");
    }

    @Override
    public Wektor negacja() {
        Wektor wynik = kopia();
        wynik.zaneguj();
        return wynik;
    }

    @Override
    public void zaneguj() {
        for (int i=0; i<liczba_elementow(); i++) {
            double wartosc = daj(i) * -1.0;
            ustaw(wartosc, i);
        }
    }

    @Override
    public void przypisz(Skalar s) {
        for (int i=0; i<liczba_elementow(); i++) {
            double wartosc = s.daj();
            ustaw(wartosc, i);
        }
    }

    @Override
    public void przypisz(Wektor w) {
        if (liczba_elementow() != w.liczba_elementow()) {
            throw new NiezgodnoscRozmiarow("Rozna liczba elementow.");
        }
        wartosci = w.wartosci.clone();
        orientacja = w.orientacja;
    }

    @Override
    public void przypisz(Macierz m) {
        throw new NiezgodnoscRozmiarow("Nie można przypisac macierzy do wektora.");
    }

    @Override
    public double daj(int... indeks) {
        sprawdzIndeks(indeks);
        Wektor nastepny = wskazniki[indeks[0]].wektor;
        if (nastepny == this) {
            return wartosci[indeks[0]];
        }
        // czyt. tablice.Macierz
        int szukaneId = wskazniki[indeks[0]].id;
        int[] pozycja = nastepny.znajdzPozycje(szukaneId);
        return nastepny.daj(pozycja[0]);
    }

    @Override
    public void ustaw(double wartosc, int... indeks) {
        sprawdzIndeks(indeks);
        Wektor nastepny = wskazniki[indeks[0]].wektor;
        wartosci[indeks[0]] = wartosc;
        // czyt. tablice.Macierz
        if (nastepny != this) {
            int szukaneId = wskazniki[indeks[0]].id;
            int[] pozycja = nastepny.znajdzPozycje(szukaneId);
            nastepny.ustaw(wartosc, pozycja[0]);
        }
    }

    @Override
    public Wektor wycinek(int... obszar) {
        sprawdzObszar(obszar);
        int dlugosc = obszar[1] - obszar[0] + 1;
        // czyt. tablice.Macierz
        Wektor wynik = new Wektor(new double[dlugosc], orientacja());
        for (int i=obszar[0]; i<=obszar[1]; i++) {
            double wartosc = daj(i);
            int ni = i - obszar[0];
            wynik.ustaw(wartosc, ni);
            wynik.wskazniki[ni].wektor = this;
            wynik.wskazniki[ni].id = id[i];
        }
        return wynik;
    }

    // czyt. tablice.Macierz
    @Override
    protected int[] znajdzPozycje(int id) {
        int[] wynik = new int[1];
        for (int i=0; i<liczba_elementow(); i++) {
            if (this.id[i] == id) {
                wynik[0] = i;
            }
        }
        return wynik;
    }

    @Override
    public int wymiar() {
        return 1;
    }

    @Override
    public int liczba_elementow() {
        return wartosci.length;
    }

    @Override
    public int[] ksztalt() {
        return new int[]{liczba_elementow()};
    }

    public boolean orientacja() {
        return orientacja;
    }

    @Override
    protected String wypisz() {
        StringBuilder stringBuilder = new StringBuilder("[");
        for (int i=0; i<liczba_elementow(); i++) {
            stringBuilder.append(daj(i));
            if (i != liczba_elementow()-1) {
                stringBuilder.append(", ");
            }
        }
        stringBuilder.append("]");
        if (!orientacja()) {
            stringBuilder.append("^T");
        }
        return stringBuilder.toString();
    }

    @Override
    public Wektor kopia() {
        double[] kopiaWartosci = new double[liczba_elementow()];
        for (int i=0; i<liczba_elementow(); i++) {
            kopiaWartosci[i] = daj(i);
        }
        return new Wektor(kopiaWartosci, orientacja());
    }

    @Override
    public void transponuj() {
        orientacja = !orientacja;
    }

    private boolean pozaZakresem(int indeks) {
        return (0 > indeks || indeks >= liczba_elementow());
    }

    @Override
    protected void sprawdzIndeks(int... indeks) {
        if (indeks.length != 1) {
            throw new ZlyIndeks("Wektor przyjmuje jeden indeks");
        }
        if (pozaZakresem(indeks[0])) {
            throw new ZlyIndeks("Indeks poza zakresem.");
        }
    }

    @Override
    protected void sprawdzObszar(int... obszar) {
        if (obszar.length != 2) {
            throw new NiezgodnoscRozmiarow("Wektor przjmuje dwa argumenty");
        }
        if (pozaZakresem(obszar[0]) || pozaZakresem(obszar[1])) {
            throw new NiezgodnoscRozmiarow("Argument poza zakresem");
        }
        if (obszar[0] > obszar[1]) {
            throw new NiezgodnoscRozmiarow("Zdegenerowany obszar");
        }

    }

    private void sprawdzWektor(Wektor w) {
        if (orientacja() != w.orientacja()) {
            throw new NiezgodnoscRozmiarow("Rozna orientacja wektorow");
        }
        if (liczba_elementow() != w.liczba_elementow()) {
            throw new NiezgodnoscRozmiarow("Rozny rozmiar wektorow");
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof Wektor)) return false;
        Wektor w = (Wektor) obj;
        if (liczba_elementow() != w.liczba_elementow()) {
            return false;
        }
        if (orientacja() != w.orientacja()) {
            return false;
        }
        for (int i=0; i<liczba_elementow(); i++) {
            if (daj(i) != w.daj(i)) {
                return false;
            }
        }
        return true;
    }
}
