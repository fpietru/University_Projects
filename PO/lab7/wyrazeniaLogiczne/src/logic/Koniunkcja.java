package logic;

public class Koniunkcja extends Operator2Arg {

    public Koniunkcja(Wyrazenie arg1, Wyrazenie arg2) {
        super(arg1, arg2);
    }

    @Override
    protected String symbol() {
        return "&&";
    }

    @Override
    protected boolean aplikuj(Wyrazenie arg1, Wyrazenie arg2) {
        return arg1.wartosc() && arg2.wartosc();
    }
}
