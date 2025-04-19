package logic;

public class Negacja extends Operator1Arg {

    public Negacja(Wyrazenie arg) {
        super(arg);
    }

    @Override
    protected String symbol() {
        return "!";
    }

    @Override
    protected boolean aplikuj(Wyrazenie arg) {
        return !(arg.wartosc());
    }
}
