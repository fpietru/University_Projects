public class Autobus extends Pojazd {
    private double zuzyciePaliwa;

    Autobus(double szybkoscMaksymalna, int numer, Zajezdnia zajezdnia, double zuzyciePaliwa) {
        super(szybkoscMaksymalna, numer, zajezdnia);
        this.zuzyciePaliwa = zuzyciePaliwa;
    }

    @Override
    public String toString() {
        return "* Autobus nr " + numer + "\n" +
                "- szybkosc maksymalna: " + szybkoscMaksymalna + " hm/h\n" +
                "- zuzycie paliwa: " + zuzyciePaliwa + "\n";
    }
}
