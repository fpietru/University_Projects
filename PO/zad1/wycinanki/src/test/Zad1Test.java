package test;

import org.junit.jupiter.api.Test;
import tablice.Macierz;
import tablice.Skalar;
import tablice.Wektor;
import tablice.wyjatki.NiezgodnoscRozmiarow;
import tablice.wyjatki.ZlyIndeks;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class Zad1Test {
    // Testy z treści zadania.
    // Wydanie kompletne.

    @Test
    void testWlasnosciSkalarow() {
        Skalar skalar = new Skalar(1.0);
        assertEquals(0, skalar.wymiar());
        assertArrayEquals(new int[]{}, skalar.ksztalt());
        assertEquals(1, skalar.liczba_elementow());
    }

    @Test
    void testWlasnosciWektorow() {
        Wektor wektor1 = new Wektor(new double[]{1.0, 2.0, 1.0}, true);
        Wektor wektor2 = new Wektor(new double[]{2.0, 2.0, 3.0}, false);
        assertEquals(1, wektor1.wymiar());
        assertArrayEquals(new int[]{3}, wektor1.ksztalt());
        assertEquals(3, wektor1.liczba_elementow());
        assertEquals(1, wektor2.wymiar());
        assertArrayEquals(new int[]{3}, wektor2.ksztalt());
        assertEquals(3, wektor2.liczba_elementow());
    }

    @Test
    void testWlasnosciMacierzy() {
        Macierz matrix = new Macierz(new double[][]{
                {1.0, 0.0, 2.0},
                {2.0, 1.0, 3.0},
                {1.0, 1.0, 1.0},
                {2.0, 3.0, 1.0}
        });
        assertEquals(2, matrix.wymiar());
        assertArrayEquals(new int[]{4, 3}, matrix.ksztalt());
        assertEquals(12, matrix.liczba_elementow());
    }

    @Test
    void testArytmetykiSkalarow() throws ZlyIndeks {
        Skalar skalar1 = new Skalar(3.5);
        Skalar skalar2 = new Skalar(11.5);
        assertEquals(new Skalar(15.0), skalar1.suma(skalar2));

        Skalar skalar3 = new Skalar(3.0);
        Skalar skalar4 = new Skalar(12.0);
        assertEquals(new Skalar(36.0), skalar3.iloczyn(skalar4));
    }

    @Test
    void testArytmetykiSkalarWektor() throws ZlyIndeks {
        for(boolean b: new boolean[]{true, false}) {
            // 3.0 + [1.0, 2.5] = [4.0, 5.5]
            Skalar skalar = new Skalar(3.0);
            Wektor wektor1 = new Wektor(new double[]{1.0, 2.5}, b);
            assertEquals(new Wektor(new double[]{4.0, 5.5}, b), skalar.suma(wektor1));

            // 4.0 * [1.5, 2.25] = [6.0, 9.0]
            Wektor wektor2 = new Wektor(new double[]{1.5, 2.25}, b);
            assertEquals(new Wektor(new double[]{6.0, 9.0}, b),
                          new Skalar(4.0).iloczyn(wektor2));
        }  // for b
    }

    @Test
    void testArytmetykiWektorSkalar() throws ZlyIndeks {
        for(boolean b: new boolean[]{true, false}) {
            // [1.0, 2.5] + 3.0 = [4.0, 5.5]
            Skalar skalar = new Skalar(3.0);
            Wektor wektor1 = new Wektor(new double[]{1.0, 2.5}, b);
            assertEquals(new Wektor(new double[]{4.0, 5.5}, b),
                           wektor1.suma(skalar));

            // [1.5, 2.25] * 4.0 = [6.0, 9.0]
            Wektor wektor2 = new Wektor(new double[]{1.5, 2.25}, b);
            assertEquals(new Wektor(new double[]{6.0, 9.0}, b),
                         wektor2.iloczyn(new Skalar(4.0)));
        }  // for b
    }

    @Test
    void testArytmetykiSkalarMacierz() throws ZlyIndeks{
        Skalar skalar = new Skalar(3.0);
        Macierz macierz = new Macierz(new double[][]{
                {1.25, 3.0, -12.0},
                {-51.0, 8.0, 3.5}
        });
        Macierz oczekiwanyWynikDodawania = new Macierz(new double[][]{
                {4.25, 6.0, -9.0},
                {-48.0, 11.0, 6.5}
        });
        assertEquals(oczekiwanyWynikDodawania, skalar.suma(macierz));

        Skalar skalar2 = new Skalar(-3.0);
        Macierz oczekiwanyWynikMnozenia = new Macierz(new double[][]{
                {-3.75, -9.0, 36.0},
                {153.0, -24.0, -10.5}
        });
        assertEquals(oczekiwanyWynikMnozenia, skalar2.iloczyn(macierz));

        // Odwrotna Kolejność
        assertEquals(oczekiwanyWynikDodawania, macierz.suma(skalar));
        assertEquals(oczekiwanyWynikMnozenia, macierz.iloczyn(skalar2));
    }

    @Test
    void testDodawaniaIMnozeniaWektorWektor() throws ZlyIndeks, NiezgodnoscRozmiarow {
        // Wektor + Wektor
        Wektor wektor1 = new Wektor(new double[]{1.0, 2.0, 3.0}, true);
        Wektor wektor2 = new Wektor(new double[]{1.0, 1.0, -2.0}, true);
        assertEquals(new Wektor(new double[]{2.0, 3.0, 1.0}, true),
                wektor1.suma(wektor2));

        Wektor wektor3 = new Wektor(new double[]{-2.0, 5.0}, false);
        Wektor wektor4 = new Wektor(new double[]{-5.0, 2.0}, false);
        assertEquals(new Wektor(new double[]{-7.0, 7.0}, false),
                wektor3.suma(wektor4));

        // Wektor * Wektor (Scalar result)
        Wektor wektor5 = new Wektor(new double[]{3.0, 2.0, -1.0}, true);
        Wektor wektor6 = new Wektor(new double[]{-2.0, 2.0, 1.0}, true);
        assertEquals(new Skalar(-3.0), wektor5.iloczyn(wektor6));

        Wektor wektor7 = new Wektor(new double[]{-2.0, -5.0, 1.0, 3.0}, false);
        Wektor wektor8 = new Wektor(new double[]{-5.0, 1.0, 2.0, -3.0}, false);
        assertEquals(new Skalar(-2.0), wektor7.iloczyn(wektor8));

        Wektor wektor9 = new Wektor(new double[]{1.0, 1.0, -2.0}, false);
        assertEquals(new Macierz(new double[][]{{-3.0}}), wektor1.iloczyn(wektor9));

        Wektor wektor10 = new Wektor(new double[]{1.0, 2.0, 3.0}, false);
        Wektor wektor11 = new Wektor(new double[]{1.0, 1.0, -2.0}, true);
        assertEquals(new Macierz(new double[][]{
                {1.0, 1.0, -2.0},
                {2.0, 2.0, -4.0},
                {3.0, 3.0, -6.0}
                }), wektor10.iloczyn(wektor11));
    }

    @Test
    void testDodawaniaWektorMacierz() throws ZlyIndeks, NiezgodnoscRozmiarow {
        // Wektor + Macierz
        Wektor wektor1 = new Wektor(new double[]{3.0, 1.5, -2.0}, true);
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, 3.5, -12.0},
                {-5.0, 8.0, 3.0}
        });
        assertEquals(new Macierz(new double[][]{
                {4.0, 5.0, -14.0},
                {-2.0, 9.5, 1.0}
        }), wektor1.suma(macierz1));

        Wektor wektor2 = new Wektor(new double[]{7.5, -5.0}, false);
        assertEquals(new Macierz(new double[][]{
                {8.5, 11.0, -4.5},
                {-10.0, 3.0, -2.0}
        }), wektor2.suma(macierz1));

        // Odwrotna Kolejność

        // Macierz + Wektor (odwrotna kolejność)
        assertEquals(new Macierz(new double[][]{
                {4.0, 5.0, -14.0},
                {-2.0, 9.5, 1.0}
        }), macierz1.suma(wektor1));

        assertEquals(new Macierz(new double[][]{
                {8.5, 11.0, -4.5},
                {-10.0, 3.0, -2.0}
        }), macierz1.suma(wektor2));

    }

    @Test
    void testMnozeniaWektorMacierz() throws ZlyIndeks, NiezgodnoscRozmiarow {
        // Wektor * Macierz
        Wektor wektor1 = new Wektor(new double[]{1.0, 2.0, 3.0}, true);
        Wektor wektor2 = new Wektor(new double[]{1.0, 1.0, -2.0}, false);
        assertEquals(new Macierz(new double[][]{{-3.0}}), wektor1.iloczyn(wektor2));

        Wektor wektor3 = new Wektor(new double[]{1.0, 2.0, 3.0}, false);
        Wektor wektor4 = new Wektor(new double[]{1.0, 1.0, -2.0}, true);
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, 1.0, -2.0},
                {2.0, 2.0, -4.0},
                {3.0, 3.0, -6.0}
        });
        assertEquals(macierz1, wektor3.iloczyn(wektor4));
    }

    @Test
    void testMnozeniaMacierzWektor() throws ZlyIndeks, NiezgodnoscRozmiarow {
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, 2.0},
                {3.0, -2.0},
                {2.0, 1.0}
        });
        Wektor wektor1 = new Wektor(new double[]{-1.0, 3.0}, false);
        Wektor oczekiwany1 = new Wektor(new double[]{5.0, -9.0, 1.0}, false);
        assertEquals(oczekiwany1, macierz1.iloczyn(wektor1));

        // [1.0, -1.0, 2.0] * [[1.0, 2.0], [3.0, -2.0], [2.0, 1.0]] = [2.0, 6.0]
        Wektor wektor2 = new Wektor(new double[]{1.0, -1.0, 2.0}, true);
        Macierz macierz2 = new Macierz(new double[][]{
                {1.0, 2.0},
                {3.0, -2.0},
                {2.0, 1.0}
        });
        Wektor oczekiwany2 = new Wektor(new double[]{2.0, 6.0}, true);
        assertEquals(oczekiwany2, wektor2.iloczyn(macierz2));
    }

    @Test
    void testDodawaniaMacierzMacierz() throws ZlyIndeks, NiezgodnoscRozmiarow {
        // [[1.0, -2.0, 3.0], [2.0, 1.0, -1.0]] + [[3.0, -1.0, 2.0], [1.0, 1.0, -2.0]] = [[4.0, -3.0, 5.0], [3.0, 2.0, -3.0]]
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, -2.0, 3.0},
                {2.0, 1.0, -1.0}
        });
        Macierz macierz2 = new Macierz(new double[][]{
                {3.0, -1.0, 2.0},
                {1.0, 1.0, -2.0}
        });
        Macierz oczekiwany = new Macierz(new double[][]{
                {4.0, -3.0, 5.0},
                {3.0, 2.0, -3.0}
        });
        assertEquals(oczekiwany, macierz1.suma(macierz2));
    }

    @Test
    void testMnozeniaMacierzMacierz() throws ZlyIndeks, NiezgodnoscRozmiarow {
        // [[2.0, 0.5], [1.0, -2.0], [-1.0, 3.0]] * [[2.0, -1.0, 5.0], [-3.0, 2.0, -1.0]] = [[2.5, -1.0, 9.5], [8.0, -5.0, 7.0], [-11.0, 7.0, -8.0]]
        Macierz macierz1 = new Macierz(new double[][]{
                {2.0, 0.5},
                {1.0, -2.0},
                {-1.0, 3.0}
        });
        Macierz macierz2 = new Macierz(new double[][]{
                {2.0, -1.0, 5.0},
                {-3.0, 2.0, -1.0}
        });
        Macierz oczekiwany = new Macierz(new double[][]{
                {2.5, -1.0, 9.5},
                {8.0, -5.0, 7.0},
                {-11.0, 7.0, -8.0}
        });
        assertEquals(oczekiwany, macierz1.iloczyn(macierz2));
    }

    @Test
    void testNegacji() {
        Skalar skalar = new Skalar(17.0);
        assertEquals(new Skalar(-17.0), skalar.negacja());

        Wektor wektor = new Wektor(new double[]{10.0, -45.0, 0.0, 29.0, -3.0}, true);
        assertEquals(new Wektor(new double[]{-10.0, 45.0, 0.0, -29.0, 3.0}, true),
                wektor.negacja());

        Macierz macierz = new Macierz(new double[][]{
                {0.0, 0.5, -1.25},
                {11.0, -71.0, -33.5},
                {-2.0, -1.75, -99.0}
        });
        Macierz oczekiwany = new Macierz(new double[][]{
                {0.0, -0.5, 1.25},
                {-11.0, 71.0, 33.5},
                {2.0, 1.75, 99.0}
        });
        assertEquals(oczekiwany, macierz.negacja());
    }

    @Test
    void testPrzypisaniaSkalarow() {
        // Przypisz skalar [0.5] do skalara [1.0]
        Skalar skalar1 = new Skalar(1.0);
        skalar1.przypisz(new Skalar(0.5));
        assertEquals(new Skalar(0.5), skalar1);

        // Przypisz skalar [0.5] do wektora [1.0, 2.0, 3.0]
        Wektor wektor1 = new Wektor(new double[]{1.0, 2.0, 3.0}, true);
        wektor1.przypisz(new Skalar(0.5));
        assertEquals(new Wektor(new double[]{0.5, 0.5, 0.5}, true), wektor1);

        // Przypisz skalar [0.5] do macierzy
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, 2.0},
                {-3.0, -4.0},
                {5.0, -6.0}
        });
        macierz1.przypisz(new Skalar(0.5));
        assertEquals(new Macierz(new double[][]{
                {0.5, 0.5},
                {0.5, 0.5},
                {0.5, 0.5}
        }), macierz1);
    }

    @Test
    void testPrzypisaniaWektorow() throws NiezgodnoscRozmiarow {
        // Przypisz wektor [1.5, 2.5, 3.5] do wektora [-1.0, 0.0, 1.0]
        Wektor wektor1 = new Wektor(new double[]{1.5, 2.5, 3.5}, false);
        Wektor wektor2 = new Wektor(new double[]{-1.0, 0.0, 1.0}, false);
        wektor2.przypisz(wektor1);
        assertEquals(new Wektor(new double[]{1.5, 2.5, 3.5}, false), wektor2);

        // Przypisz wektor [1.5, 2.5, 3.5] do wektora [-1.0, 0.0, 1.0] (wektor wierszowy i kolumnowy)
        Wektor wektor3 = new Wektor(new double[]{-1.0, 0.0, 1.0}, true);
        wektor3.przypisz(wektor1);
        assertEquals(new Wektor(new double[]{1.5, 2.5, 3.5}, false), wektor3);

        // Przypisz wektor [1.5, 2.5, 3.5] do macierzy
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, 2.0, -1.0, -2.0},
                {-3.0, -4.0, 3.0, 4.0},
                {5.0, -6.0, -5.0, 6.0}
        });
        macierz1.przypisz(wektor1);
        assertEquals(new Macierz(new double[][]{
                {1.5, 1.5, 1.5, 1.5},
                {2.5, 2.5, 2.5, 2.5},
                {3.5, 3.5, 3.5, 3.5}
        }), macierz1);
    }

    @Test
    void testPrzypisaniaMacierzy() throws NiezgodnoscRozmiarow {
        // Przypisz macierz [10.5, 20.5, 30.5; -1.5, 0.0, 1.5] do macierzy [1.0, 2.0, 3.0; 3.0, 2.0, 1.0]
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, 2.0, 3.0},
                {3.0, 2.0, 1.0}
        });
        Macierz macierz2 = new Macierz(new double[][]{
                {10.5, 20.5, 30.5},
                {-1.5, 0.0, 1.5}
        });

        macierz1.przypisz(macierz2);
        assertEquals(macierz2, macierz1);
    }

    @Test
    void testWycinkow() {
        Skalar skalar = new Skalar(13.125);
        assertEquals(skalar, skalar.wycinek());

        Wektor wektor = new Wektor(new double[]{1.0, 21.0, 32.0, 43.0, 54.0}, true);
        Wektor oczekiwanyWycinekWektora = new Wektor(new double[]{32.0, 43.0}, true);
        assertEquals(oczekiwanyWycinekWektora, wektor.wycinek(2, 3));

        Macierz macierz = new Macierz(new double[][]{
                {7.0, -21.0, 15.0, -31.0, 25.0},
                {-21.0, 15.0, -31.0, 25.0, 7.0},
                {15.0, -31.0, 25.0, -7.0, -21.0},
                {-31.0, 25.0, 7.0, -21.0, 15.0}
        });
        Macierz oczekiwanyWycinekMacierzy = new Macierz(new double[][]{
                {15.0, -31.0},
                {-31.0, 25.0},
                {25.0, 7.0}
        });
        assertEquals(oczekiwanyWycinekMacierzy, macierz.wycinek(1, 3, 1, 2));
    }

    @Test
    void testUstawianiePrzezWycinek() {
        Macierz macierz = new Macierz(new double[][]{
                {1.0, 2.0, 3.0},
                {4.0, 5.0, 6.0},
                {7.0, 8.0, 9.0}
        });

        Macierz wycinek = macierz.wycinek(1, 2, 1, 2);  // fragment: [[5.0, 6.0], [8.0, 9.0]]
        wycinek.ustaw(99.0, 0, 0); // zmieniamy element [1][1] w oryginalnej macierzy

        assertEquals(99.0, macierz.daj(1, 1));
        assertEquals(99.0, wycinek.daj(0, 0));
    }

    @Test
    void testWielokrotnyWycinek() {
        Macierz macierz = new Macierz(new double[][]{
                {1.0, 2.0, 3.0},
                {4.0, 5.0, 6.0},
                {7.0, 8.0, 9.0}
        });

        Macierz pierwszy = macierz.wycinek(0, 2, 0, 2);  // calosc
        Macierz drugi = pierwszy.wycinek(1, 2, 1, 2);    // [[5.0, 6.0], [8.0, 9.0]]
        assertEquals(new Macierz(new double[][]{
                {5.0, 6.0},
                {8.0, 9.0}
        }), drugi);
    }

    @Test
    void testBlednyWycinekMacierzy() {
        Macierz macierz = new Macierz(new double[][]{
                {1.0, 2.0},
                {3.0, 4.0}
        });

        // Zakres poza rozmiarem
        try {
            macierz.wycinek(1, 2, 0, 1);
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }

        // Zdegenerowany obszar (od > do)
        try {
            macierz.wycinek(1, 0, 0, 1);
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testBlednyWycinekWektora() {
        Wektor w = new Wektor(new double[]{10.0, 20.0, 30.0}, true);

        try {
            w.wycinek(-1, 1);
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }

        try {
            w.wycinek(2, 1); // od > do
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testTranspozycjaWycinkaNieZmieniaOryginalu() {
        Macierz macierz = new Macierz(new double[][]{
                {1.0, 2.0, 3.0},
                {4.0, 5.0, 6.0}
        });

        Macierz wycinek = macierz.wycinek(0, 1, 0, 1); // [[1.0, 2.0], [4.0, 5.0]]
        wycinek.transponuj();

        assertEquals(1.0, macierz.daj(0, 0));
        assertEquals(2.0, macierz.daj(0, 1));
        assertEquals(4.0, macierz.daj(1, 0));
        assertEquals(5.0, macierz.daj(1, 1));
    }

    @Test
    void testTranspozycjaOryginaluNieZmieniaWycinka() {
        Macierz macierz = new Macierz(new double[][]{
                {1.0, 2.0},
                {3.0, 4.0}
        });

        Macierz wycinek = macierz.wycinek(0, 0, 0, 1); // [[1.0, 2.0]]
        macierz.transponuj(); // teraz oryginał to [[1.0, 3.0], [2.0, 4.0]]

        // Wycinek nadal powinien pokazywac pierwotny widok
        Macierz oczekiwanyWynik = new Macierz(new double[][]{{1.0, 2.0}});
        assertEquals(wycinek, oczekiwanyWynik);
    }

    @Test
    void testDrzewoWycinkow() {
        Macierz macierz = new Macierz(new double[][]{
                {1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 10, 11, 12}
        });

        Macierz a = macierz.wycinek(0, 2, 1, 3); // kolumny 1-3
        Macierz b = a.wycinek(1, 2, 0, 1); // macierz [[6, 7], [10, 11]]
        Macierz c = b.wycinek(1, 1, 1, 1); // tylko [11]

        // Zmiana jednego elementu w najglebszym wycinku
        c.ustaw(99, 0, 0);

        assertEquals(99, macierz.daj(2, 2)); // macierz[2][2] = 11 -> 99
        assertEquals(99, a.daj(2, 1));
        assertEquals(99, b.daj(1, 1));
        assertEquals(99, c.daj(0, 0));
    }

    @Test
    void testKopiaVsWycinek() {
        Macierz macierz = new Macierz(new double[][]{
                {1.0, 2.0},
                {3.0, 4.0}
        });

        Macierz wycinek = macierz.wycinek(0, 1, 0, 1);
        Macierz kopia = wycinek.kopia();

        // Zmieniamy wycinek
        wycinek.ustaw(99.0, 0, 0);

        // Kopia powinna zostać nienaruszona
        assertEquals(99.0, macierz.daj(0, 0));
        assertEquals(1.0, kopia.daj(0, 0));
    }

    @Test
    void testPrzypisanieDoWycinka() {
        Macierz macierz = new Macierz(new double[][]{
                {0.0, 0.0},
                {0.0, 0.0}
        });

        Macierz wycinek = macierz.wycinek(0, 1, 0, 0); // pierwsza kolumna
        wycinek.przypisz(new Skalar(7.0));

        assertEquals(7.0, macierz.daj(0, 0));
        assertEquals(7.0, macierz.daj(1, 0));
    }

    @Test
    void testWycinekSkalaru() {
        Skalar skalar = new Skalar(3.14);
        Skalar wycinek = skalar.wycinek();

        assertEquals(new Skalar(3.14), wycinek);

        wycinek.przypisz(new Skalar(2.0));
        assertEquals(2.0, skalar.daj());
    }

    @Test
    void testDodajSkalar() {
        Macierz macierz = new Macierz(new double[][]{
                {1.0, 2.0},
                {3.0, 4.0}
        });

        macierz.dodaj(new Skalar(2.0));

        assertEquals(new Macierz(new double[][]{
                {3.0, 4.0},
                {5.0, 6.0}
        }), macierz);
    }

    @Test
    void testDodajMacierz() {
        Macierz m1 = new Macierz(new double[][]{
                {1.0, 2.0},
                {3.0, 4.0}
        });

        Macierz m2 = new Macierz(new double[][]{
                {5.0, 6.0},
                {7.0, 8.0}
        });

        m1.dodaj(m2);

        assertEquals(new Macierz(new double[][]{
                {6.0, 8.0},
                {10.0, 12.0}
        }), m1);
    }

    @Test
    void testPrzemnozSkalar() {
        Macierz m = new Macierz(new double[][]{
                {1.0, 2.0},
                {3.0, -1.0}
        });

        m.przemnoz(new Skalar(2.0));

        assertEquals(new Macierz(new double[][]{
                {2.0, 4.0},
                {6.0, -2.0}
        }), m);
    }

    @Test
    void testPrzemnozWektorThrows() {
        Macierz m = new Macierz(new double[][]{
                {1.0, 2.0},
                {3.0, 4.0}
        });

        Wektor w = new Wektor(new double[]{1.0, 2.0}, false);

        try {
            m.przemnoz(w);
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testWypisywanieSkalar() {
        Skalar s = new Skalar(3.14);
        assertEquals("[3.14]", s.toString());
    }

    @Test
    void testWypisywanieWektor() {
        Wektor w1 = new Wektor(new double[]{1.0, 2.5, -3.0}, true);
        Wektor w2 = new Wektor(new double[]{1.0, 2.5, -3.0}, false);

        assertEquals("[1.0, 2.5, -3.0]", w1.toString());
        assertEquals("[1.0, 2.5, -3.0]^T", w2.toString());
    }

    @Test
    void testWypisywanieMacierzy() {
        Macierz m = new Macierz(new double[][] {
                {1.0, 2.0},
                {3.0, 4.0}
        });

        String expected = "[[1.0, 2.0]\n[3.0, 4.0]]";
        assertEquals(expected, m.toString());
    }

    @Test
    void testPrzemnozMacierzNadpisuje() {
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, 2.0},
                {3.0, 4.0}
        });

        Macierz macierz2 = new Macierz(new double[][]{
                {2.0, 0.0},
                {1.0, 2.0}
        });

        macierz1.przemnoz(macierz2); // macierz1 *= macierz2

        Macierz oczekiwany = new Macierz(new double[][]{
                {4.0, 4.0},
                {10.0, 8.0}
        });

        assertEquals(oczekiwany, macierz1);
    }

    @Test
    void testZleIndeksyMacierzy() {
        Macierz m = new Macierz(new double[][]{
                {1.0, 2.0},
                {3.0, 4.0}
        });

        // Indeks poza zakresem
        try {
            m.daj(2, 0); // 2 > maks. index wiersza
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.ZlyIndeks", e.getClass().getName());
        }

        try {
            m.daj(0, 2); // 2 > maks. index kolumny
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.ZlyIndeks", e.getClass().getName());
        }

        // Za mało indeksów
        try {
            m.daj(0); // tylko jeden
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.ZlyIndeks", e.getClass().getName());
        }

        // Za dużo indeksów
        try {
            m.daj(0, 1, 2); // trzy indeksy
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.ZlyIndeks", e.getClass().getName());
        }
    }


    @Test
    void testZleIndeksyWektora() {
        Wektor w = new Wektor(new double[]{1.0, 2.0, 3.0}, true);

        try {
            w.daj(3); // indeks poza zakresem
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.ZlyIndeks", e.getClass().getName());
        }

        try {
            w.daj(); // brak indeksu
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.ZlyIndeks", e.getClass().getName());
        }

        try {
            w.daj(1, 2); // za duzo indeksow
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.ZlyIndeks", e.getClass().getName());
        }
    }

    @Test
    void testZleIndeksySkalar() {
        Skalar s = new Skalar(7.0);

        try {
            s.daj(0); // skalar nie przyjmuje indeksow
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.ZlyIndeks", e.getClass().getName());
        }

        try {
            s.ustaw(1.0, 1); // za dużo argumentow
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.ZlyIndeks", e.getClass().getName());
        }
    }

    @Test
    void testZlyWycinekMacierzy() {
        Macierz m = new Macierz(new double[][]{
                {1.0, 2.0},
                {3.0, 4.0}
        });

        // Zakres poza rozmiarem
        try {
            m.wycinek(1, 3, 0, 1);
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }

        // Od > do
        try {
            m.wycinek(1, 0, 0, 1);
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }

        // Za mało argumentów
        try {
            m.wycinek(1, 2, 1); // tylko 3 argumenty
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }

        // Za dużo argumentów
        try {
            m.wycinek(0, 1, 0, 1, 0);
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testZlyWycinekWektora() {
        Wektor w = new Wektor(new double[]{1.0, 2.0, 3.0}, true);

        // Indeks poza zakresem
        try {
            w.wycinek(0, 3);
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }

        // Od > do
        try {
            w.wycinek(2, 1);
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }

        // Zla liczba argumentów
        try {
            w.wycinek(1); // tylko jeden argument
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testZlyWycinekSkalar() {
        Skalar s = new Skalar(42.0);

        try {
            s.wycinek(0); // nie przyjmuje zadnych argumentow
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testDodajSkalarSkalar() {
        Skalar s = new Skalar(1);
        s.dodaj(new Skalar(1));
        assertEquals(new Skalar(2), s);

    }

    @Test
    void testDodajSkalarWektor() {
        Skalar s = new Skalar(1);
        try {
            s.dodaj(new Wektor(new double[]{1, 2, 3}, true));
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testDodajSkalarMacierz() {
        Skalar s = new Skalar(1);
        try {
            s.dodaj(new Macierz(new double[][]{{1, 2, 3}, {4, 5, 6}}));
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testPrzemnozSkalarSkalar() {
        Skalar s = new Skalar(1);
        s.przemnoz(new Skalar(2));
        assertEquals(new Skalar(2), s);
    }

    @Test
    void testPrzemnozSkalarWektor() {
        Skalar s = new Skalar(1);
        try {
            s.przemnoz(new Wektor(new double[]{1, 2, 3}, true));
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testPrzemnozSkalarMacierz() {
        Skalar s = new Skalar(1);
        try {
            s.przemnoz(new Macierz(new double[][]{{1, 2, 3}, {4, 5, 6}}));
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testZanegujSkalar() {
        Skalar s = new Skalar(1);
        s.zaneguj();
        assertEquals(new Skalar(-1), s);
    }

    @Test
    void testPrzypiszSkalarWektor() {
        Skalar s = new Skalar(1);
        try {
            s.przypisz(new Wektor(new double[]{1, 2, 3}, true));
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testPrzypiszSkalarMacierz() {
        Skalar s = new Skalar(1);
        try {
            s.przypisz(new Macierz(new double[][]{{1, 2, 3}, {4, 5, 6}}));
        } catch (Exception e) {
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testTransponujSkalar() {
        Skalar s = new Skalar(1);
        s.transponuj();
        assertEquals(new Skalar(1), s);
    }

    @Test
    void testDodajWektorSkalar() {
        Wektor w = new Wektor(new double[]{1, 2, 3}, true);
        w.dodaj(new Skalar(1));
        assertEquals(new Wektor(new double[]{2,3,4}, true), w);
    }

    @Test
    void testDodajWektorWektor() {
        Wektor w = new Wektor(new double[]{1, 2, 3}, true);
        w.dodaj(new Wektor(new double[]{3, 2, 1}, true));
        assertEquals(new Wektor(new double[]{4,4,4}, true), w);
    }

    @Test
    void testDodajWektorMacierz() {
        Wektor w = new Wektor(new double[]{1, 2, 3}, true);
        try {
            w.dodaj(new Macierz(new double[][]{{1, 2, 3}, {4, 5, 6}}));
        } catch (Exception e){
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testPrzemnozWektorSkalar() {
        Wektor w = new Wektor(new double[]{1, 2, 3}, true);
        w.przemnoz(new Skalar(2));
        assertEquals(new Wektor(new double[]{2, 4, 6}, true), w);
    }

    @Test
    void testPrzemnozWektorWektor() {
        Wektor w = new Wektor(new double[]{1, 2, 3}, true);
        try {
            w.przemnoz(new Wektor(new double[]{1, 2, 3}, true));
        } catch (Exception e){
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testPrzemnozWektorMacierz() {
        Wektor w = new Wektor(new double[]{1, 2, 3}, true);
        try {
            w.przemnoz(new Macierz(new double[][]{{1, 2, 3}, {4, 5, 6}}));
        } catch (Exception e){
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

    @Test
    void testTransponujWektor() {
        Wektor w = new Wektor(new double[]{1, 2, 3}, true);
        w.transponuj();
        assertEquals(new Wektor(new double[]{1, 2, 3}, false), w);
    }

    @Test
    void testPrzypiszMacierzWektor() {
        Macierz m = new Macierz(new double[3][2]);
        m.przypisz(new Wektor(new double[]{1, 2}, true));
        assertEquals(new Macierz(new double[][]{{1,2}, {1,2}, {1,2}}), m);

        m.przypisz(new Wektor(new double[]{1,2,3}, false));
        assertEquals(new Macierz(new double[][]{{1,1}, {2,2}, {3,3}}), m);
    }

    @Test
    void testZanegujMacierz() {
        Macierz m = new Macierz(new double[][]{{1,2}, {3, 4}});
        m.zaneguj();
        assertEquals(new Macierz(new double[][]{{-1,-2}, {-3,-4}}), m);
    }

    @Test
    void testDodajMacierzWektor() {
        Macierz m = new Macierz(new double[][]{{1,2}, {3, 4}});
        Wektor w = new Wektor(new double[]{1, 1}, true);
        m.dodaj(w);
        assertEquals(new Macierz(new double[][]{{2,3}, {4, 5}}), m);
    }

    @Test
    void testPrzypiszWektorMacierz() {
        Wektor w = new Wektor(new double[]{1, 2, 3}, false);
        try {
            w.przypisz(new Macierz(new double[2][2]));
        } catch (Exception e){
            assertEquals("tablice.wyjatki.NiezgodnoscRozmiarow", e.getClass().getName());
        }
    }

}
