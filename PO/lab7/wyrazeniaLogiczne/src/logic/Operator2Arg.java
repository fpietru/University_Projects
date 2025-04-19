package logic;

public abstract class Operator2Arg extends Wyrazenie {
    protected Wyrazenie arg1;
    protected Wyrazenie arg2;

    public Operator2Arg(Wyrazenie arg1, Wyrazenie arg2) {
        this.arg1 = arg1;
        this.arg2 = arg2;
    }

    protected abstract String symbol();
    protected abstract boolean aplikuj(Wyrazenie arg1, Wyrazenie arg2);

    @Override
    public boolean wartosc() {
        return aplikuj(arg1, arg2);
    }

    @Override
    public String toString() {
        return "(" + arg1 + ")" + symbol() + "(" + arg2 + ")";
    }
}
