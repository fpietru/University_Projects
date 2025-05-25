package uzycie;

import tablice.*;

public class Main {
    public static void main (String[] args) {
        Macierz m = new Macierz(new double[][]{{1,2,3}, {4,5,6}});
        System.out.println("Macierz m:\n" + m);

        Wektor w = new Wektor(new double[]{1, 0}, true);
        System.out.println("Wektor w:\n" + w);
        w.transponuj();
        System.out.println("Po transpozycji:\n" + w);

        Macierz m2 = m.wycinek(0, 1, 0, 1);
        System.out.println("Wycinek m:\n" + m2);

        Skalar s = new Skalar(9);
        System.out.println("Skalar s:\n" + s);

        m2.przypisz(s);
        System.out.println("Po przypisaniu s do wycinka m macierz m to:\n" + m);

    }
}
