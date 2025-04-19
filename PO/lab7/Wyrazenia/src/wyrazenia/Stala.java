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
        return new Stala(0.);
    }

    @Override
    public String wypisz() {
        return Double.toString(wartosc);
    }

    @Override
    public Wyrazenie dodaj(Wyrazenie w) {
        if (wartosc == 0) {
            return w;
        }
        return w.dodajOdwr(this);
    }

    @Override
    protected  Wyrazenie dodajOdwr(Wyrazenie w) {
        if (wartosc == 0) {
            return w;
        }
        return new Suma(w, this);
    }

    @Override
    public double calkaOzn(double a, double b, int n) {
        // System.out.println("szybka wersja");
        return wartosc * (b - a);
    }

}
