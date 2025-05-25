/*
    Autor: Franciszek Pietrusiak
*/
package tablice;

import tablice.wyjatki.*;

public class Macierz extends Tablica {

    /*
        Niech W bedzie wycinkiem macierzy M.
        Obiekty klasy Wskaznik sa wykorzystywane w metodzie
        daj i ustaw, aby W posiadal uaktualnione wartosci
        wzgledem M oraz mogl propagowac zmiany wartosci do M.
        Kazdy element macierzy ma przypisany do siebie unikalny id,
        ktory nie zmienia sie przy operacjach arytmetycznych i
        transpozycji.
    */
    private static class Wskaznik {
        public Macierz macierz;
        public int id;

        public Wskaznik(Macierz macierz, int id) {
            this.macierz = macierz;
            this.id = id;
        }

        public Wskaznik kopia() {
            return new Wskaznik(macierz, id);
        }
    }

    private double[][] wartosci;
    private int[][] id;
    private Wskaznik[][] wskazniki;

    public Macierz(double[][] wartosci) {
        super(2);
        this.wartosci = wartosci;
        /*
            Kazda macierz jest wycinkiem innej macierzy (byc moze samej siebie).
            Przy inicjacji macierz jest wycinkiem samej siebie,
            wiec kazdy element macierzy wskazuje na samego siebie.
        */
        int licznik = 0;
        id = new int[liczbaWierszy()][liczbaKolumn()];
        wskazniki = new Wskaznik[liczbaWierszy()][liczbaKolumn()];
        for (int i=0; i<liczbaWierszy(); i++) {
            for (int j=0; j<liczbaKolumn(); j++) {
                id[i][j] = licznik++;
                wskazniki[i][j] = new Wskaznik(this, id[i][j]);
            }
        }
    }

    @Override
    public Macierz suma(Skalar s) {
        Macierz wynik = kopia();
        for (int i=0; i<liczbaWierszy(); i++) {
            for (int j=0; j<liczbaKolumn(); j++) {
                double wartosc = wynik.daj(i, j) + s.daj();
                wynik.ustaw(wartosc, i, j);
            }
        }
        return wynik;
    }

    @Override
    public Macierz suma(Wektor w) {
        sprawdzWektor(w);
        Macierz wynik = kopia();
        if (w.orientacja()) { // poziomy wektor
            for (int i=0; i<liczbaWierszy(); i++) {
                for (int j=0; j<liczbaKolumn(); j++) {
                    double wartosc = wynik.daj(i, j) + w.daj(j);
                    wynik.ustaw(wartosc, i, j);
                }
            }
        } else { // pionowy wektor
            for (int j=0; j<liczbaKolumn(); j++) {
                for (int i=0; i<liczbaWierszy(); i++) {
                    double wartosc = wynik.daj(i, j) + w.daj(i);
                    wynik.ustaw(wartosc, i, j);
                }
            }
        }
        return wynik;
    }

    @Override
    public Macierz suma(Macierz m) {
        sprawdzMacierz(m);
        Macierz wynik = kopia();
        for (int i=0; i<liczbaWierszy(); i++) {
            for (int j=0; j<liczbaKolumn(); j++) {
                double wartosc = wynik.daj(i, j) + m.daj(i, j);
                wynik.ustaw(wartosc, i, j);
            }
        }
        return wynik;
    }

    @Override
    public void dodaj(Skalar s) {
        przypisz(suma(s));
    }

    @Override
    public void dodaj(Wektor w) {
        przypisz(suma(w));
    }

    @Override
    public void dodaj(Macierz m) {
        przypisz(suma(m));
    }

    @Override
    public Macierz iloczyn(Skalar s) {
        Macierz wynik = kopia();
        for (int i=0; i<liczbaWierszy(); i++) {
            for (int j=0; j<liczbaKolumn(); j++) {
                double wartosc = wynik.daj(i, j) * s.daj();
                wynik.ustaw(wartosc, i, j);
            }
        }
        return wynik;
    }

    @Override
    public Wektor iloczyn(Wektor w) {
        if (w.orientacja()) {
            throw new NiezgodnoscRozmiarow("Wynik nie bedzie wektorem.");
        }
        if (w.liczba_elementow() != liczbaKolumn()) {
            throw new NiezgodnoscRozmiarow("Nie mozna pomnozyc przez wektor tego ksztaltu.");
        }
        Wektor wynik = new Wektor(new double[liczbaWierszy()], false);
        for (int i=0; i<liczbaWierszy(); i++) {
            double wartosc = 0.0;
            for (int j=0; j<liczbaKolumn(); j++) {
                wartosc += daj(i, j) * w.daj(j);
            }
            wynik.ustaw(wartosc, i);
        }
        return wynik;
    }

    @Override
    public Macierz iloczyn(Macierz m) {
        if (liczbaKolumn() != m.liczbaWierszy()) {
            throw new NiezgodnoscRozmiarow("Zly ksztalt przy mnozeniu");
        }
        Macierz wynik = new Macierz(new double[liczbaWierszy()][m.liczbaKolumn()]);
        for (int i=0; i<liczbaWierszy(); i++) {
            for (int j=0; j<m.liczbaKolumn(); j++) {
                double wartosc = 0.0;
                for (int k=0; k<liczbaKolumn(); k++) {
                    wartosc += daj(i, k) * m.daj(k, j);
                }
                wynik.ustaw(wartosc, i, j);
            }
        }
        return wynik;
    }

    @Override
    public void przemnoz(Skalar s) {
        przypisz(iloczyn(s));
    }

    @Override
    public void przemnoz(Wektor w) {
        throw new NiezgodnoscRozmiarow("Wynikiem mnozenia nie jest macierz.");
    }

    @Override
    public void przemnoz(Macierz m) {
        Macierz pom = iloczyn(m);
        sprawdzMacierz(pom);
        przypisz(pom);
    }

    @Override
    public Macierz negacja() {
        Macierz wynik = kopia();
        for (int i=0; i<liczbaWierszy(); i++) {
            for (int j=0; j<liczbaKolumn(); j++) {
                double wartosc = wynik.daj(i, j) * -1.0;
                wynik.ustaw(wartosc, i, j);
            }
        }
        return wynik;
    }

    @Override
    public void zaneguj() {
        przypisz(negacja());
    }

    @Override
    public void przypisz(Skalar s) {
        for (int i=0; i<liczbaWierszy(); i++) {
            for (int j=0; j<liczbaKolumn(); j++) {
                double wartosc = s.daj();
                ustaw(wartosc, i, j);
            }
        }
    }

    @Override
    public void przypisz(Wektor w) {
        sprawdzWektor(w);
        if (w.orientacja()) { // poziomy wektor
            for (int i=0; i<liczbaWierszy(); i++) {
                for (int j=0; j<liczbaKolumn(); j++) {
                    double wartosc = w.daj(j);
                    ustaw(wartosc, i, j);
                }
            }
        } else { // pionowy wektor
            for (int j=0; j<liczbaKolumn(); j++) {
                for (int i=0; i<liczbaWierszy(); i++) {
                    double wartosc = w.daj(i);
                    ustaw(wartosc, i, j);
                }
            }
        }
    }

    @Override
    public void przypisz(Macierz m) {
        for (int i=0; i<liczbaWierszy(); i++) {
            for (int j=0; j<liczbaKolumn(); j++) {
                double wartosc = m.daj(i, j);
                ustaw(wartosc, i, j);
            }
        }
    }

    @Override
    public double daj(int... indeks) {
        sprawdzIndeks(indeks);
        Macierz nastepny = wskazniki[indeks[0]][indeks[1]].macierz;
        if (nastepny == this) {
            return wartosci[indeks[0]][indeks[1]];
        }
        /*
            Jesli nastepny != this to rekurencyjnie wywoluje
            metode daj dla nastepnej macierzy i sprawdzam
            wartosc pod indeksem odpowiadającym szukanemu id.
         */
        int szukaneId = wskazniki[indeks[0]][indeks[1]].id;
        int[] pozycja = nastepny.znajdzPozycje(szukaneId);
        return nastepny.daj(pozycja[0], pozycja[1]);
    }

    @Override
    public void ustaw(double wartosc, int... indeks) {
        sprawdzIndeks(indeks);
        Macierz nastepny = wskazniki[indeks[0]][indeks[1]].macierz;
        wartosci[indeks[0]][indeks[1]] = wartosc;
        /*
            Jesli nastepny != this to rekurencyjnie wywoluje
            metode ustaw dla nastepnej macierzy, gdzie zmieniam
            wartosc na pozycji odpowiadajacej szukanemu id.
         */
        if (nastepny != this) {
            int szukaneId = wskazniki[indeks[0]][indeks[1]].id;
            int[] pozycja = nastepny.znajdzPozycje(szukaneId);
            nastepny.ustaw(wartosc, pozycja[0], pozycja[1]);
        }
    }

    @Override
    public Macierz wycinek(int... obszar) {
        sprawdzObszar(obszar);
        int wysokosc = obszar[1] - obszar[0] + 1;
        int szerokosc = obszar[3] - obszar[2] + 1;
        /*
            Tworze wycinek W z macierzy M i kazdemu elementowi
            w \in W przypisuje odpowiadajacy mu element z m \in M
            co zapisuje w tablicy wskazniki[][].
        */
        Macierz wynik = new Macierz(new double[wysokosc][szerokosc]);
        for (int i=obszar[0]; i<=obszar[1]; i++) {
            for (int j=obszar[2]; j<=obszar[3]; j++) {
                double wartosc = daj(i, j);
                int ni = i - obszar[0];
                int nj = j - obszar[2];
                wynik.ustaw(wartosc, ni, nj);
                wynik.wskazniki[ni][nj].macierz = this;
                wynik.wskazniki[ni][nj].id = id[i][j];
            }
        }
        return wynik;
    }

    // Zwraca pozycje elementu ktoremu odpowiada zadany id.
    @Override
    protected int[] znajdzPozycje(int id) {
        int[] wynik = new int[2];
        for (int i=0; i<liczbaWierszy(); i++) {
            for (int j=0; j<liczbaKolumn(); j++) {
                if (this.id[i][j] == id) {
                    wynik[0] = i;
                    wynik[1] = j;
                }
            }
        }
        return wynik;
    }

    @Override
    public int wymiar() {
        return 2;
    }

    @Override
    public int liczba_elementow() {
        return liczbaWierszy() * liczbaKolumn();
    }

    @Override
    public int[] ksztalt() {
        return new int[]{liczbaWierszy(), liczbaKolumn()};
    }

    @Override
    protected String wypisz() {
        StringBuilder stringBuilder = new StringBuilder("[");
        for (int i=0; i<liczbaWierszy(); i++) {
            stringBuilder.append("[");
            for (int j=0; j<liczbaKolumn(); j++) {
                stringBuilder.append(daj(i, j));
                if (j != liczbaKolumn() - 1) {
                    stringBuilder.append(", ");
                }
            }
            stringBuilder.append("]");
            if (i != liczbaWierszy() - 1) {
                stringBuilder.append("\n");
            }
        }
        stringBuilder.append("]");
        return stringBuilder.toString();
    }

    @Override
    public Macierz kopia() {
        double[][] kopiaWartosci = new double[liczbaWierszy()][liczbaKolumn()];
        for (int i=0; i<liczbaWierszy(); i++) {
            for (int j=0; j<liczbaKolumn(); j++)
                kopiaWartosci[i][j] = daj(i, j);
        }
        return new Macierz(kopiaWartosci);
    }

    @Override
    public void transponuj() {
        double[][] noweWartosci = new double[liczbaKolumn()][liczbaWierszy()];
        Wskaznik[][] noweWskazniki = new Wskaznik[liczbaKolumn()][liczbaWierszy()];
        int[][] noweId = new int[liczbaKolumn()][liczbaWierszy()];
        int licznik = 0;
        for (int i=0; i<liczbaWierszy(); i++) {
            for (int j=0; j<liczbaKolumn(); j++) {
                noweWartosci[j][i] = wartosci[i][j];
                noweWskazniki[j][i] = wskazniki[i][j].kopia();
                noweId[j][i] = licznik++;
            }
        }
        wartosci = noweWartosci;
        wskazniki = noweWskazniki;
        id = noweId;
    }

    private int liczbaWierszy() {
        return wartosci.length;
    }

    private int liczbaKolumn() {
        return wartosci[0].length;
    }

    private boolean pozaZakresem(int... indeks) {
        boolean pierwszaWsp = (0 > indeks[0] || indeks[0] >= liczbaWierszy());
        boolean drugaWsp = (0 > indeks[1] || indeks[1] >= liczbaKolumn());
        return pierwszaWsp || drugaWsp;
    }

    @Override
    protected void sprawdzIndeks(int... indeks) {
        if (indeks.length != 2) {
            throw new ZlyIndeks("Macierz przyjmuje dwa indeksy");
        }
        if (pozaZakresem(indeks)) {
            throw new ZlyIndeks("Indeks poza zakresem.");
        }
    }

    @Override
    protected void sprawdzObszar(int... obszar) {
        if (obszar.length != 4) {
            throw new NiezgodnoscRozmiarow("Macierz przyjmuje 4 argumenty");
        }
        if (pozaZakresem(obszar[0], obszar[2]) || pozaZakresem(obszar[1], obszar[3])) {
            throw new NiezgodnoscRozmiarow("Obszar poza zakresem");
        }
        if (obszar[0] > obszar[1] || obszar[2] > obszar[3]) {
            throw new NiezgodnoscRozmiarow("Zdegenerowany obszar");
        }
    }

    private void sprawdzWektor(Wektor w) {
        if (!w.orientacja() && w.liczba_elementow() != liczbaWierszy()) {
            throw new NiezgodnoscRozmiarow("Pionowy wektor ma rozna liczbe elementow od liczby wierszy macierzy.");
        }
        if (w.orientacja() && w.liczba_elementow() != liczbaKolumn()) {
            throw new NiezgodnoscRozmiarow("Poziomy wektor ma rozna liczbe elementow od liczby kolumn macierzy.");
        }
    }

    private void sprawdzMacierz(Macierz m) {
        if (liczbaWierszy() != m.liczbaWierszy()) {
            throw new NiezgodnoscRozmiarow("Macierze maja rozna liczbe wierszy.");
        } else if (liczbaKolumn() != m.liczbaKolumn()) {
            throw new NiezgodnoscRozmiarow("Macierze maja rozna liczbe kolumn.");
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof Macierz)) return false;
        Macierz m = (Macierz) obj;
        if (liczbaWierszy() != m.liczbaWierszy() || liczbaKolumn() != m.liczbaKolumn()) {
            return false;
        }
        for (int i=0; i<liczbaWierszy(); i++) {
            for (int j=0; j<liczbaKolumn(); j++) {
                if (daj(i, j) != m.daj(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }
}
