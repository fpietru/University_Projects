package logic;

public abstract class Operator1Arg extends Wyrazenie {
    protected Wyrazenie arg;
    protected String symbol;

    public Operator1Arg(Wyrazenie arg, String symbol) {
        this.arg = arg;
        this.symbol = symbol;
    }

    protected abstract boolean aplikuj(boolean x);

    @Override
    public boolean wartosc(boolean x) {
        return aplikuj(arg.wartosc(x));
    }

    @Override
    public String toString() {
        return symbol + "(" + arg + ")";
    }
}
