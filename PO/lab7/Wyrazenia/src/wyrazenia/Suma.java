package wyrazenia;

public class Suma extends Operator2Arg {
    public Suma(Wyrazenie arg1, Wyrazenie arg2) {
        super(arg1, arg2);
    }

    @Override
    protected int priorytet() {
        return 2;
    }

    @Override
    protected double aplikuj(double w1, double w2) {
        return w1 + w2;
    }

    @Override
    protected String symbol() {
        return "+";
    }

    @Override
    public Wyrazenie pochodna() {
        return arg1.pochodna().dodaj(arg2.pochodna());
    }
}
