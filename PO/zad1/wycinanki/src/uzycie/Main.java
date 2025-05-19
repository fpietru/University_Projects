package uzycie;

import tablice.*;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class Main {
    public static void main (String[] args) {
        /*Wektor wektor1 = new Wektor(new double[]{3.0, 1.5, -2.0}, true);
        System.out.println(wektor1);

        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, 3.5, -12.0},
                {-5.0, 8.0, 3.0}
        });
        System.out.println(macierz1);
        */
        /*assertEquals(new Macierz(new double[][]{
                {4.0, 5.0, -14.0},
                {-2.0, 9.5, 1.0}
        }), wektor1.suma(macierz1));
       */

        /*Wektor wektor2 = new Wektor(new double[]{7.5, -5.0}, false);
        System.out.println(wektor2);

        Tablica m = wektor2.suma(macierz1);
        System.out.println(m);
        */
        /*assertEquals(new Macierz(new double[][]{
                {8.5, 11.0, -4.5},
                {-10.0, 3.0, -2.0}
        }), wektor2.suma(macierz1));
        */

        Skalar skalar = new Skalar(3.0);
        Macierz macierz = new Macierz(new double[][]{
                {1.25, 3.0, -12.0},
                {-51.0, 8.0, 3.5}
        });

        System.out.println(skalar);
        System.out.println(macierz);

        Macierz oczekiwanyWynikDodawania = new Macierz(new double[][]{
                {4.25, 6.0, -9.0},
                {-48.0, 11.0, 6.5}
        });

        assertEquals(oczekiwanyWynikDodawania, skalar.suma(macierz));

        System.out.println(macierz);


        Skalar skalar2 = new Skalar(-3.0);
        Macierz oczekiwanyWynikMnozenia = new Macierz(new double[][]{
                {-3.75, -9.0, 36.0},
                {153.0, -24.0, -10.5}
        });
        assertEquals(oczekiwanyWynikMnozenia, skalar2.iloczyn(macierz));


    }
}
