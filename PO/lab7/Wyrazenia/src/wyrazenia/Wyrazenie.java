package wyrazenia;

public abstract class Wyrazenie {
    public Wyrazenie(){};
    public abstract double wartosc(double x);
    public abstract Wyrazenie pochodna();
    public abstract String wypisz();
    protected int priorytet(){
        return Integer.MAX_VALUE;
    }
    public double calkaOzn(double a, double b) {
        return calkaOzn(a, b, 100);
    }

    public double calkaOzn(double a, double b, int n) {
        assert(a < b);
        double res = 0.0;
        double lewy = wartosc(a);
        double delta = (b-a) / n;
        for (int i=1; i<=n; i++) {
            double prawy = wartosc(a + i * delta);
            res += (lewy + prawy) * delta / 2;
            lewy = prawy;
        }
        return res;
    }
}
