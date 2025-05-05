package logic;

public class Zmienna extends Wyrazenie {
    public Zmienna() {}

    @Override
    public boolean wartosc(boolean x) {
        return x;
    }

    @Override
    public String toString() {
        return "x";
    }
}
