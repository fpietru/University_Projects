package wyrazenia;

public class Iloczyn extends Operator2Arg {

    public Iloczyn(Wyrazenie arg1, Wyrazenie arg2) {
        super(arg1, arg2);
    }

    @Override
    protected int priorytet() {
        return 1000;
    }

    @Override
    protected double aplikuj(double w1, double w2) {
        return w1 * w2;
    }

    @Override
    protected String symbol() {
        return "*";
    }

    @Override
    public Wyrazenie pochodna() {
        return new Iloczyn(arg1, arg2.pochodna())
                .dodaj(new Iloczyn(arg1.pochodna(), arg2));
    }
}
