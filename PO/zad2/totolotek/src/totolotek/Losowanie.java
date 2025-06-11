package totolotek;

import java.util.Set;
import java.util.TreeSet;

public class Losowanie {
    private int numer;
    private Zaklad wynik;

    public Losowanie(int numer) {
        this.numer = numer;
        this.wynik = new Zaklad();
    }

    public Losowanie(int numer, Zaklad zaklad) {
        this.numer = numer;
        this.wynik = zaklad;
    }

    public int dajNumer() {
        return numer;
    }

    public int porownaj(Zaklad zaklad) {
        Set<Integer> przeciecie = new TreeSet<>(wynik.dajLiczby());
        przeciecie.retainAll(zaklad.dajLiczby());
        return przeciecie.size();
    }


    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Losowanie nr ");
        sb.append(numer);
        sb.append("\n");
        sb.append("Wyniki: ");
        sb.append(wynik);
        return sb.toString();
    }
}
