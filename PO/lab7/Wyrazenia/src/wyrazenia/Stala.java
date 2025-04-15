package wyrazenia;

public class Stala extends Wyrazenie {
    private double wartosc;

    public Stala(double wartosc) {
        this.wartosc = wartosc;
    }

    @Override
    public double wartosc(double x) {
        return wartosc;
    }

    @Override
    public Wyrazenie pochodna() {
        return new Stala(0);
    }

    @Override
    public String wypisz() {
        return Double.toString(wartosc);
    }
}
