package przyklad;

import logic.*;

public class Main {
    public static void main(String[] args) {
        Wyrazenie s = new Stala(true);
        System.out.println("Stala s wypisuje sie jako " + s
            + " bo ma wartosc w punkcie true " + s.wartosc(true)
            + " i w punkcie false " + s.wartosc(false));

        Wyrazenie ns = new Negacja(s);
        System.out.println("Negacja stalej s wypisuje sie jako " + ns
            + " oraz ma wartosc w punkcie true " + ns.wartosc(true)
            + " i w punkcie false " + ns.wartosc(false));


        Wyrazenie z = new Zmienna();
        System.out.println("Zmienna z wypisuje sie jako " + z
            + " oraz ma wartosc w punkcie true " + z.wartosc(true)
            + " i w punkcie false " + z.wartosc(false));

        Wyrazenie nz = new Negacja(z);
        System.out.println("Negacja zmiennej z wypisuje sie jako " + nz
            + " oraz ma wartosc w punkcie true " + nz.wartosc(true)
            + " i w punkcie false " + nz.wartosc(false));

        System.out.println("Tabelka koniunkcji stalej a, b: ");
        for (int i=0; i<=1; i++) {
            for (int j=0; j<=1; j++) {
                Stala a = new Stala((i==1));
                Stala b = new Stala((j==1));
                Wyrazenie k = new Koniunkcja(a, b);
                Wyrazenie l = new Alternatywa(a, b);
                System.out.println(
                        a + " = " + a.wartosc(true) + " , " +
                        b + " = " + b.wartosc(true) + " , " +
                        k + " = " + k.wartosc(true) + " , " +
                        l + " = " + l.wartosc(true)
                );
            }
        }

        System.out.println("Jakies dlugie wyrazenie");
        Wyrazenie d = new Negacja(
                new Koniunkcja(new Alternatywa(new Negacja(new Zmienna()), new Stala(false)), nz));
        System.out.println(d + " w punkcie true ma wartosc " + d.wartosc(true)
            + " a w punkcie false " + d.wartosc(false));
    }
}
