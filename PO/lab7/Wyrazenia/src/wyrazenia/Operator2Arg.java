package wyrazenia;

public abstract class Operator2Arg extends Wyrazenie {
    protected Wyrazenie arg1;
    protected Wyrazenie arg2;

    public Operator2Arg(Wyrazenie arg1, Wyrazenie arg2) {
        this.arg1 = arg1;
        this.arg2 = arg2;
    }

    @Override
    public double wartosc(double x) {
        return aplikuj(arg1.wartosc(x), arg2.wartosc(x));
    }

    protected abstract double aplikuj(double w1, double w2);

    @Override
    public String wypisz() {
        String res = arg1.wypisz();
        if (arg1.priorytet() < priorytet()) {
            res = "(" + res + ")";
        }
        res += " " + symbol() + " ";
        if (arg2.priorytet() < priorytet()) {
            res += "(" + arg2.wypisz() + ")";
        } else {
            res += arg2.wypisz();
        }
        return res;
    }

    protected abstract String symbol();
}
