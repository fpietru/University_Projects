package logic;

public abstract class Operator2Arg extends Wyrazenie {
    protected Wyrazenie arg1;
    protected Wyrazenie arg2;
    protected String symbol;

    public Operator2Arg(Wyrazenie arg1, Wyrazenie arg2, String symbol) {
        this.arg1 = arg1;
        this.arg2 = arg2;
        this.symbol = symbol;
    }

    protected abstract boolean aplikuj(boolean x, boolean y);

    @Override
    public boolean wartosc(boolean x) {
        return aplikuj(arg1.wartosc(x), arg2.wartosc(x));
    }

    @Override
    public String toString() {
        return "(" + arg1 + ")" + symbol + "(" + arg2 + ")";
    }
}
