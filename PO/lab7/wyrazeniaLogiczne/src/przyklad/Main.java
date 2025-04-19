package przyklad;

import logic.*;

public class Main {
    public static void main(String[] args) {
        Wyrazenie s = new Stala(true);
        System.out.println("Stala s wypisuje sie jako " + s
            + " bo ma wartosc " + s.wartosc());

        Wyrazenie ns = new Negacja(s);
        System.out.println("Negacja stalej s wypisuje sie jako " + ns
            + " oraz ma wartosc " + ns.wartosc());

        Wyrazenie z = new Zmienna(true, "p");
        System.out.println("Zmienna z wypisuje sie jako " + z
                + " oraz ma wartosc " + z.wartosc());

        Wyrazenie nz = new Negacja(z);
        System.out.println("Negacja zmiennej z wypisuje sie jako " + nz
                + " oraz ma wartosc " + nz.wartosc());

        System.out.println("Tabelka koniunkcji zmiennej a,b: ");
        for (int i=0; i<=1; i++) {
            for (int j=0; j<=1; j++) {
                Zmienna a = new Zmienna((i==1), "a");
                Zmienna b = new Zmienna((j==1), "b");
                Wyrazenie k = new Koniunkcja(a, b);
                Wyrazenie l = new Alternatywa(a, b);
                System.out.println(a + " = " + a.wartosc() + " , " +
                        b + " = " + b.wartosc() + " , " +
                        k + " = " + k.wartosc() + " , " +
                        l + " = " + l.wartosc());
            }
        }

        System.out.println("Jakies dlugie wyrazenie");
        Wyrazenie d = new Negacja(
                new Koniunkcja(new Alternatywa(new Negacja(new Zmienna(true, "z")), new Stala(false)), nz));
        System.out.println(d + " = " + d.wartosc());
    }
}
