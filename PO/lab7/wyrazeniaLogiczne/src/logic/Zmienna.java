package logic;

public class Zmienna extends Wyrazenie {
    private boolean wartosc;
    private String symbol;

    public Zmienna(boolean wartosc, String symbol) {
        this.wartosc = wartosc;
        this.symbol = symbol;
    }

    @Override
    public boolean wartosc() {
        return wartosc;
    }

    @Override
    public String toString() {
        return symbol;
    }
}
