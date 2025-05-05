package logic;

public class Koniunkcja extends Operator2Arg {

    public Koniunkcja(Wyrazenie arg1, Wyrazenie arg2) {
        super(arg1, arg2, "&&");
    }

    @Override
    protected boolean aplikuj(boolean x, boolean y) {
        return x && y;
    }
}
