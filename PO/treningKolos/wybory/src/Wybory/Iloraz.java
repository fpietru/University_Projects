package Wybory;

public class Iloraz implements Comparable<Iloraz> {
    private double wartosc;
    private Komitet komitet;

    public Iloraz(double wartosc, Komitet komitet) {
        this.wartosc = wartosc;
        this.komitet = komitet;
    }

    public double getWartosc() {
        return wartosc;
    }

    public Komitet getKomitet() {
        return komitet;
    }

    @Override
    public int compareTo(Iloraz inny) {
        if (this.wartosc > inny.wartosc) return -1;
        else if (this.wartosc < inny.wartosc) return 1;
        else return 0;
    }
}
