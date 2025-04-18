public class Tramwaj extends Pojazd {
    private int iloscWagonow;

    Tramwaj(double szybkoscMaksymalna, int numer, Zajezdnia zajezdnia, int iloscWagonow) {
        super(szybkoscMaksymalna, numer, zajezdnia);
        this.iloscWagonow = iloscWagonow;
    }

    @Override
    public String toString() {
        return "* Tramwaj nr " + numer + "\n" +
                "- szybkosc maksymalna: " + szybkoscMaksymalna + " hm/h\n" +
                "- ilosc wagonow: " + iloscWagonow + "\n";
    }
}
