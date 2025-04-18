public class Pojazd {
    protected double szybkoscMaksymalna;
    protected int numer;
    protected Zajezdnia zajezdnia;

    Pojazd(double szybkoscMaksymalna, int numer, Zajezdnia zajezdnia) {
        this.szybkoscMaksymalna = szybkoscMaksymalna;
        this.numer = numer;
        this.zajezdnia = zajezdnia;
    }

    public void setZajezdnia(Zajezdnia zajezdnia) {
        this.zajezdnia = zajezdnia;
    }
}
