package wyrazenia;

public class Zmienna extends Wyrazenie {

    private static Zmienna INSTANCJA = null;

    public static Zmienna dajInstancje() {
        if (INSTANCJA == null) {
            INSTANCJA = new Zmienna();
        }
        return INSTANCJA;
    }

    private Zmienna() {}

    @Override
    public double wartosc(double x) {
        return x;
    }

    @Override
    public Wyrazenie pochodna() {
        return new Stala(1);
    }

    @Override
    public String wypisz() {
        return "x";
    }
}
