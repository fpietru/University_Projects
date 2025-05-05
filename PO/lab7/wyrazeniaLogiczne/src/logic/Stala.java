package logic;

public class Stala extends Wyrazenie {
    private final boolean wartosc;

    public Stala(boolean wartosc) {
        this.wartosc = wartosc;
    }

    @Override
    public boolean wartosc(boolean x) {
        return wartosc;
    }

    @Override
    public String toString() {
        return wartosc ? "T" : "F";
    }
}
