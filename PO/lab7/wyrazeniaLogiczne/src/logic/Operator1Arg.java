package logic;

public abstract class Operator1Arg extends Wyrazenie {
    protected Wyrazenie arg;

    public Operator1Arg(Wyrazenie arg) {
        this.arg = arg;
    }

    protected abstract String symbol();
    protected abstract boolean aplikuj(Wyrazenie arg);

    @Override
    public boolean wartosc() {
        return aplikuj(arg);
    }

    @Override
    public String toString() {
        return symbol() + "(" + arg + ")";
    }
}
