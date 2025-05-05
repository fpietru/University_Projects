package logic;

public class Negacja extends Operator1Arg {

    public Negacja(Wyrazenie arg) {
        super(arg, "!");
    }

    @Override
    protected boolean aplikuj(boolean x) { return !x; }
}
