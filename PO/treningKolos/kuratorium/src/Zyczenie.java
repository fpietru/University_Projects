public class Zyczenie implements Comparable<Zyczenie> {
    public static final int NIEWIADOMO = 0;
    public static final int PRZYJETE = 1;
    public static final int ODRZUCONE = 2;

    private Klasa klasa;
    private Uczen uczen;
    private int numer;
    private int pozycja;
    private int status;
    private int punkty;

    public Zyczenie(Klasa klasa, Uczen uczen, int numer) {
        this.klasa = klasa;
        this.uczen = uczen;
        this.numer = numer;
        this.status = NIEWIADOMO;
    }

    public Klasa getKlasa() { return klasa; }
    public Uczen getUczen() { return uczen; }
    public int getNumer() { return numer; }
    public int getPozycja() { return pozycja; }
    public int getStatus() { return status; }

    public void setPozycja(int pozycja) { this.pozycja = pozycja; }
    public void setStatus(int status) { this.status = status; }

    @Override
    public int compareTo(Zyczenie inne) {
        if (this.punkty > inne.punkty) return -1;
        else if (this.punkty < inne.punkty) return 1;
        else return 0;
    }
}
