package tablice;

import wyjatki.NiezgodnoscRozmiarow;
import wyjatki.ZlyIndeks;
import wyjatki.ZlyKsztalt;
import wyjatki.ZlyWymiar;

public class Macierz extends Tablica {
    private double[][] wartosci;

    public Macierz(double[][] wartosci) {
        super(2);
        this.wartosci = wartosci;
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
            throw new ZlyKsztalt("Wynik nie bedzie wektorem.");
        }
        if (w.liczba_elementow() != liczbaKolumn()) {
            throw new ZlyKsztalt("Nie mozna pomnozyc przez wektor tego ksztaltu.");
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
            throw new ZlyKsztalt("Zly ksztalt przy mnozeniu");
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
        throw new ZlyWymiar("Wynikiem mnozenia nie jest macierz.");
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
        return wartosci[indeks[0]][indeks[1]];
    }

    @Override
    public void ustaw(double wartosc, int... indeks) {
        sprawdzIndeks(indeks);
        wartosci[indeks[0]][indeks[1]] = wartosc;
    }

    @Override
    public Macierz wycinek(int... obszar) {
        return null;
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
                stringBuilder.append(wartosci[i][j]);
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
                kopiaWartosci[i][j] = wartosci[i][j];
        }
        return new Macierz(kopiaWartosci);
    }

    @Override
    public void transponuj() {
        double[][] noweWartosci = new double[liczbaKolumn()][liczbaWierszy()];
        for (int i=0; i<liczbaWierszy(); i++) {
            for (int j=0; j<liczbaKolumn(); j++) {
                noweWartosci[j][i] = wartosci[i][j];
            }
        }
        wartosci = noweWartosci;
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

    }

    private void sprawdzWektor(Wektor w) {
        if (!w.orientacja() && w.liczba_elementow() != liczbaWierszy()) {
            throw new ZlyKsztalt("Pionowy wektor ma rozna liczbe elementow od liczby wierszy macierzy.");
        }
        if (w.orientacja() && w.liczba_elementow() != liczbaKolumn()) {
            throw new ZlyKsztalt("Poziomy wektor ma rozna liczbe elementow od liczby kolumn macierzy.");
        }
    }

    private void sprawdzMacierz(Macierz m) {
        if (liczbaWierszy() != m.liczbaWierszy()) {
            throw new ZlyKsztalt("Macierze maja rozna liczbe wierszy.");
        } else if (liczbaKolumn() != m.liczbaKolumn()) {
            throw new ZlyKsztalt("Macierze maja rozna liczbe kolumn.");
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
