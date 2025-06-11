package totolotek;

import org.junit.jupiter.api.Test;

import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import static org.junit.jupiter.api.Assertions.*;

class ZakladTest {

    @Test
    void tworzenieLosowegoZakladu() {
        Zaklad zaklad = new Zaklad();
        Set<Integer> liczby = zaklad.dajLiczby();
        assertEquals(6, liczby.size());
        for (int liczba : liczby) {
            assertTrue(liczba >= 1 && liczba <= 49);
        }
    }

    @Test
    void tworzenieNielosowegoZakladu() {
        Set<Integer> liczby = new TreeSet<>(Set.of(1, 2, 3, 4, 5, 6));
        Zaklad zaklad = new Zaklad(liczby);
        assertEquals(liczby, zaklad.dajLiczby());
    }

    @Test
    void tworzenieZakladuZNieprawidlowaLiczbaLiczb() {
        Set<Integer> zaMalo = Set.of(1, 2, 3, 4, 5);
        Set<Integer> zaDuzo = new TreeSet<>(Set.of(1, 2, 3, 4, 5, 6, 7));

        assertThrows(IllegalArgumentException.class, () -> new Zaklad(zaMalo));
        assertThrows(IllegalArgumentException.class, () -> new Zaklad(zaDuzo));
    }

    @Test
    void tworzenieZakladuZNieprawidlowymiLiczbami() {
        Set<Integer> zaMala = Set.of(0, 1, 2, 3, 4, 5);
        Set<Integer> zaDuza = Set.of(1, 2, 3, 4, 5, 50);

        assertThrows(IllegalArgumentException.class, () -> new Zaklad(zaMala));
        assertThrows(IllegalArgumentException.class, () -> new Zaklad(zaDuza));
    }

    @Test
    void testToString() {
        Set<Integer> liczby = new TreeSet<>(Set.of(1, 10, 20, 30, 40, 49));
        Zaklad zaklad = new Zaklad(liczby);
        String expected = "  1  10  20  30  40  49 ";
        assertEquals(expected, zaklad.toString());
    }


    @Test
    void unikalnoscLiczbWZakladzie() {
        Zaklad zaklad = new Zaklad();
        Set<Integer> liczby = zaklad.dajLiczby();
        assertEquals(6, liczby.size());
        assertEquals(6, liczby.stream().distinct().count());
    }
}


class BlankietTest {

    @Test
    void tworzenieBlankietu() {
        Blankiet blankiet = new Blankiet();
        assertNotNull(blankiet);
    }

    @Test
    void skreslanieKratek() {
        Blankiet blankiet = new Blankiet();
        blankiet.skreslKratke(1, 1);
        blankiet.skreslKratke(1, 2);
        blankiet.skreslKratke(1, 3);
        blankiet.skreslKratke(1, 4);
        blankiet.skreslKratke(1, 5);
        blankiet.skreslKratke(1, 6);
        assertTrue(blankiet.szescSkreslonych(1));
        assertEquals(6, blankiet.dajZaklady().getFirst().dajLiczby().size());
    }

    @Test
    void skreslanieNieprawidlowychKratek() {
        Blankiet blankiet = new Blankiet();
        assertThrows(IllegalArgumentException.class, () -> blankiet.skreslKratke(0, 1));
        assertThrows(IllegalArgumentException.class, () -> blankiet.skreslKratke(9, 1));
        assertThrows(IllegalArgumentException.class, () -> blankiet.skreslKratke(1, 0));
        assertThrows(IllegalArgumentException.class, () -> blankiet.skreslKratke(1, 50));
    }

    @Test
    void anulowanieZakladu() {
        Blankiet blankiet = new Blankiet();
        blankiet.anulujZaklad(1);
        assertTrue(blankiet.czyAnulowany(1));
    }

    @Test
    void dajZakladyZPominieciemNieprawidlowych() {
        Blankiet blankiet = new Blankiet();
        // Zaklad 1: prawidlowy
        blankiet.skreslKratke(1, 1);
        blankiet.skreslKratke(1, 2);
        blankiet.skreslKratke(1, 3);
        blankiet.skreslKratke(1, 4);
        blankiet.skreslKratke(1, 5);
        blankiet.skreslKratke(1, 6);

        // Zaklad 2: anulowany
        blankiet.anulujZaklad(2);

        // Zaklad 3: za malo skreslen
        blankiet.skreslKratke(3, 1);
        blankiet.skreslKratke(3, 2);

        List<Zaklad> zaklady = blankiet.dajZaklady();
        assertEquals(1, zaklady.size());
    }

    @Test
    void skreslanieLiczbyLosowan() {
        Blankiet blankiet = new Blankiet();
        blankiet.skreslLiczbeLosowan(5);
        assertEquals(5, blankiet.dajLiczbeLosowan());

        blankiet.skreslLiczbeLosowan(10);
        assertEquals(10, blankiet.dajLiczbeLosowan());
    }

    @Test
    void skreslanieNieprawidlowejLiczbyLosowan() {
        Blankiet blankiet = new Blankiet();
        assertThrows(IllegalArgumentException.class, () -> blankiet.skreslLiczbeLosowan(0));
        assertThrows(IllegalArgumentException.class, () -> blankiet.skreslLiczbeLosowan(11));
    }

    @Test
    void domyslnaLiczbaLosowan() {
        Blankiet blankiet = new Blankiet();
        assertEquals(1, blankiet.dajLiczbeLosowan());
    }

    @Test
    void skreslanieWszystkichKratekWPolu() {
        Blankiet blankiet = new Blankiet();
        for (int i = 1; i <= 49; i++) {
            blankiet.skreslKratke(1, i);
        }
        assertFalse(blankiet.szescSkreslonych(1));
    }

    @Test
    void wielokrotneSkreslanieTejSamejKratki() {
        Blankiet blankiet = new Blankiet();
        blankiet.skreslKratke(1, 1);
        blankiet.skreslKratke(1, 1); // drugi raz tę samą
        assertEquals(1, blankiet.skreslonychWpolu[0]);
    }

    @Test
    void kilkaPoprawnychZakladow() {
        Blankiet blankiet = new Blankiet();
        // 3 poprawne zaklady
        for (int z = 1; z <= 3; z++) {
            for (int l = 1; l <= 6; l++) {
                blankiet.skreslKratke(z, l);
            }
        }
        assertEquals(3, blankiet.dajZaklady().size());
    }
}


class KuponTest {

    @Test
    void tworzenieKuponu() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        List<Zaklad> zaklady = List.of(new Zaklad(), new Zaklad());
        int liczbaLosowan = 3;

        Kupon kupon = new Kupon(centrala, kolektura, zaklady, liczbaLosowan);

        assertNotNull(kupon.dajIdentyfikator());
        assertEquals(kolektura, kupon.dajKolekture());
        assertEquals(zaklady.size(), kupon.dajZaklady().size());
        assertEquals(liczbaLosowan, kupon.dajLiczbeLosowan());
    }

    @Test
    void numeracjaKuponow() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        List<Zaklad> zaklady = List.of(new Zaklad());

        Kupon kupon1 = new Kupon(centrala, kolektura, zaklady, 1);
        Kupon kupon2 = new Kupon(centrala, kolektura, zaklady, 1);

        assertNotEquals(kupon1.dajIdentyfikator(), kupon2.dajIdentyfikator());
    }

    @Test
    void identyfikatorKuponu() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        List<Zaklad> zaklady = List.of(new Zaklad());

        Kupon kupon = new Kupon(centrala, kolektura, zaklady, 1);
        String id = kupon.dajIdentyfikator();

        String[] parts = id.split("-");
        assertEquals(4, parts.length);
        assertEquals(1, parts[0].length()); // numer kuponu
        assertEquals(1, parts[1].length()); // numer kolektury
    }

    @Test
    void bierzeUdzialWLosowaniu() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        List<Zaklad> zaklady = List.of(new Zaklad());

        Kupon kupon = new Kupon(centrala, kolektura, zaklady, 3);

        assertTrue(kupon.bierzeUdzialWLosowaniu(new Losowanie(1)));
        assertTrue(kupon.bierzeUdzialWLosowaniu(new Losowanie(2)));
        assertTrue(kupon.bierzeUdzialWLosowaniu(new Losowanie(3)));
        assertFalse(kupon.bierzeUdzialWLosowaniu(new Losowanie(4)));
    }

    @Test
    void cenaKuponu() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        List<Zaklad> zaklady = List.of(new Zaklad(), new Zaklad(), new Zaklad());
        int liczbaLosowan = 5;

        Kupon kupon = new Kupon(centrala, kolektura, zaklady, liczbaLosowan);
        assertEquals(3 * 5 * 300, kupon.dajCene());
        assertEquals(3 * 5 * 60, kupon.dajPodatek());
    }
}


class KolekturaTest {

    @Test
    void tworzenieKolektury() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);

        assertEquals(1, centrala.liczbaKolektor());
        assertEquals(1, kolektura.dajNumer());
    }

    @Test
    void transakcjaUdana() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        Gracz gracz = new Minimalista("Jan", "Kowalski",
                "123456789", 1000, centrala, new Kolektura[]{kolektura});

        assertTrue(kolektura.transakcja(gracz, 1, 1));
        assertEquals(700, gracz.dajSrodkiFinansowe());
    }

    @Test
    void transakcjaNieudana() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        Gracz gracz = new Minimalista("Jan", "Kowalski",
                "123456789", 200, centrala, new Kolektura[]{kolektura});

        assertFalse(kolektura.transakcja(gracz, 1, 1));
        assertEquals(200, gracz.dajSrodkiFinansowe());
    }

    @Test
    void kuponNaChybilTrafil() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        Gracz gracz = new Minimalista("Jan", "Kowalski",
                "123456789", 1000, centrala, new Kolektura[]{kolektura});

        kolektura.kuponNaChybilTrafil(2, 1, gracz);

        assertEquals(400, gracz.dajSrodkiFinansowe());
        assertEquals(1, gracz.kupony.size());
    }

    @Test
    void kuponZBlankietu() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        Gracz gracz = new Minimalista("Jan", "Kowalski",
                "123456789", 1000, centrala, new Kolektura[]{kolektura});

        Blankiet blankiet = new Blankiet();
        blankiet.skreslKratke(1, 1);
        blankiet.skreslKratke(1, 2);
        blankiet.skreslKratke(1, 3);
        blankiet.skreslKratke(1, 4);
        blankiet.skreslKratke(1, 5);
        blankiet.skreslKratke(1, 6);
        blankiet.skreslLiczbeLosowan(2);

        kolektura.kuponZBlankietu(blankiet, gracz);

        assertEquals(400, gracz.dajSrodkiFinansowe());
        assertEquals(1, gracz.kupony.size());
    }

    @Test
    void wyplataWygranej() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);

        // Symulacja wygranej
        Set<Integer> liczby = Set.of(1, 2, 3, 4, 5, 6);
        List<Zaklad> zaklady = List.of(new Zaklad(liczby));
        Zaklad zwycieski = zaklady.getFirst();
        Gracz gracz = new Staloliczbowy("Jan", "Kowalski",
                "123456789", 10000, centrala, zwycieski, new Kolektura[]{kolektura});

        gracz.zagraj();
        centrala.przeprowadzLosowanie(zwycieski);
        gracz.odbierzIleSieDa();

        assertTrue(gracz.dajSrodkiFinansowe() > 10000);
    }

    @Test
    void sprzedazKuponuZPustymBlankietem() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        Gracz gracz = new Minimalista("Jan", "Kowalski", "123456789", 1000, centrala, new Kolektura[]{kolektura});

        Blankiet blankiet = new Blankiet();
        kolektura.kuponZBlankietu(blankiet, gracz);

        assertEquals(0, gracz.dajKupony().size());
        assertEquals(1000, gracz.dajSrodkiFinansowe());
    }
}

class CentralaTest {

    @Test
    void tworzenieCentrali() {
        BudzetPanstwa budzet = new BudzetPanstwa();
        Centrala centrala = new Centrala(budzet);

        assertEquals(0, centrala.liczbaKolektor());
        assertEquals(0, centrala.liczbaWydrukowanychKuponow());
        assertEquals(0, centrala.liczbaLosowan());
    }

    @Test
    void dodawanieKolektury() {
        BudzetPanstwa budzet = new BudzetPanstwa();
        Centrala centrala = new Centrala(budzet);
        new Kolektura(centrala);

        assertEquals(1, centrala.liczbaKolektor());
    }

    @Test
    void przyjmowaniePrzychodu() {
        BudzetPanstwa budzet = new BudzetPanstwa();
        Centrala centrala = new Centrala(budzet);

        centrala.przyjmijPrzychod(1, 1000);

        assertEquals(800, centrala.dajSrodkiFinansowe(1));
        assertEquals(200, budzet.dajPodatki());
    }

    @Test
    void przeprowadzanieLosowania() {
        BudzetPanstwa budzet = new BudzetPanstwa();
        Centrala centrala = new Centrala(budzet);

        long milion = 100000000;
        centrala.przyjmijPrzychod(1, milion);
        centrala.przeprowadzLosowanie();

        assertEquals(1, centrala.liczbaLosowan());
        assertTrue(centrala.dajSumeSrodkow() > 0);
    }

    @Test
    void kumulacjaNagrody() {
        BudzetPanstwa budzet = new BudzetPanstwa();
        Centrala centrala = new Centrala(budzet);

        centrala.przyjmijPrzychod(1, 1000000);
        centrala.przeprowadzLosowanie();

        Long[] nagrody = centrala.dajNagrodyDlaLosowania(1);
        assertTrue(centrala.dajKumulacje() >= nagrody[1]);
    }

    @Test
    void pokrywanieKosztowZSubwencji() {
        BudzetPanstwa budzet = new BudzetPanstwa();
        Centrala centrala = new Centrala(budzet);

        long subwencja = centrala.pokryjKoszt(1000000);

        assertEquals(1000000, subwencja);
        assertEquals(1000000, budzet.dajSubwencje());
    }


    @Test
    void gwarantowanaPulaNagrodyIStopnia() {
        BudzetPanstwa budzet = new BudzetPanstwa();
        Centrala centrala = new Centrala(budzet);

        centrala.przyjmijPrzychod(1, 100000); // mala kwota
        centrala.przeprowadzLosowanie();

        Long[] nagrody = centrala.dajNagrodyDlaLosowania(1);
        assertTrue(nagrody[1] >= 200000000); // 2 mln zl gwarantowane
    }

    @Test
    void minimalnaNagrodaIIIStopnia() {
        BudzetPanstwa budzet = new BudzetPanstwa();
        Centrala centrala = new Centrala(budzet);

        centrala.przyjmijPrzychod(1, 100000);
        centrala.przeprowadzLosowanie();

        Long[] nagrody = centrala.dajNagrodyDlaLosowania(1);
        assertTrue(nagrody[3] >= 3600); // 36 zl minimalnie na zaklad
    }

    @Test
    void kumulacjaPrzyBrakujacejSzostce() {
        BudzetPanstwa budzet = new BudzetPanstwa();
        Centrala centrala = new Centrala(budzet);

        centrala.przyjmijPrzychod(1, 1000000);
        centrala.przeprowadzLosowanie();

        // Symulacja ze nikt nie trafil szostki
        long kumulacja = centrala.dajKumulacje();
        assertTrue(kumulacja > 0);

        // Drugie losowanie - kumulacja powinna byc dodana
        centrala.przyjmijPrzychod(2, 1000000);
        centrala.przeprowadzLosowanie();
        Long[] nagrody = centrala.dajNagrodyDlaLosowania(2);
        assertTrue(nagrody[1] >= kumulacja);
    }
}


class BudzetPanstwaTest {

    @Test
    void tworzenieBudzetu() {
        BudzetPanstwa budzet = new BudzetPanstwa();
        assertEquals(0, budzet.dajPodatki());
        assertEquals(0, budzet.dajSubwencje());
    }

    @Test
    void zbieraniePodatkow() {
        BudzetPanstwa budzet = new BudzetPanstwa();
        budzet.zbierzPodatek(1000);
        assertEquals(1000, budzet.dajPodatki());
    }

    @Test
    void przekazywanieSubwencji() {
        BudzetPanstwa budzet = new BudzetPanstwa();
        long subwencja = budzet.przekazSubwencje(1000);
        assertEquals(1000, subwencja);
        assertEquals(1000, budzet.dajSubwencje());
    }

    @Test
    void wielokrotnePobieranieSubwencji() {
        BudzetPanstwa budzet = new BudzetPanstwa();
        long kwota1 = budzet.przekazSubwencje(1000);
        long kwota2 = budzet.przekazSubwencje(2000);

        assertEquals(1000, kwota1);
        assertEquals(2000, kwota2);
        assertEquals(3000, budzet.dajSubwencje());
    }

    @Test
    void podatekOdWysokiejWygranej() {
        BudzetPanstwa budzet = new BudzetPanstwa();
        Centrala centrala = new Centrala(budzet);
        Kolektura kolektura = new Kolektura(centrala);

        // Symulacja wysokiej wygranej (>2280 zl)
        Set<Integer> liczby = Set.of(1, 2, 3, 4, 5, 6);
        List<Zaklad> zaklady = List.of(new Zaklad(liczby));
        Zaklad zwycieski = zaklady.getFirst();

        Gracz gracz = new Staloliczbowy("Jan", "Kowalski",
                "123456789", 1000000, centrala,
                zwycieski, new Kolektura[]{kolektura});

        gracz.zagraj();
        centrala.przeprowadzLosowanie(zwycieski);

        long podatkiPrzed = budzet.dajPodatki();
        gracz.odbierzIleSieDa();
        long podatkiPo = budzet.dajPodatki();

        assertTrue(podatkiPo > podatkiPrzed);
    }
}


class LosowanieTest {

    @Test
    void tworzenieLosowania() {
        Losowanie losowanie = new Losowanie(1);
        assertEquals(1, losowanie.dajNumer());
        assertNotNull(losowanie);
    }

    @Test
    void testToString() {
        Losowanie losowanie = new Losowanie(123);
        String result = losowanie.toString();
        assertTrue(result.startsWith("Losowanie nr 123"));
        assertTrue(result.contains("Wyniki:"));
    }
}

class GraczTest {

    @Test
    void tworzenieGracza() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        Gracz gracz = new Minimalista("Jan", "Kowalski",
                "123456789", 1000, centrala, new Kolektura[]{kolektura});

        assertEquals("Jan", gracz.imie);
        assertEquals("Kowalski", gracz.nazwisko);
        assertEquals("123456789", gracz.pesel);
        assertEquals(1000, gracz.dajSrodkiFinansowe());
    }

    @Test
    void przyjmowanieKuponu() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        Gracz gracz = new Minimalista("Jan", "Kowalski",
                "123456789", 1000, centrala, new Kolektura[]{kolektura});

        Kupon kupon = new Kupon(centrala, kolektura, List.of(new Zaklad()), 1);
        gracz.przyjmijKupon(kupon);

        assertEquals(1, gracz.dajKupony().size());
        assertEquals(kupon, gracz.dajKupony().getFirst());
    }

    @Test
    void operacjeFinansowe() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        Gracz gracz = new Minimalista("Jan", "Kowalski",
                "123456789", 1000, centrala, new Kolektura[]{kolektura});

        gracz.zwiekszSrodkiFinansowe(500);
        assertEquals(1500, gracz.dajSrodkiFinansowe());

        gracz.zmniejszSrodkiFinansowe(300);
        assertEquals(1200, gracz.dajSrodkiFinansowe());
    }

    @Test
    void sprawdzanieKuponowPoLosowaniu() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        Gracz gracz = new Minimalista("Jan", "Kowalski",
                "123456789", 1000, centrala, new Kolektura[]{kolektura});

        Kupon kupon = new Kupon(centrala, kolektura, List.of(new Zaklad()), 1);
        gracz.przyjmijKupon(kupon);

        centrala.przyjmijPrzychod(1, 100000);
        centrala.przeprowadzLosowanie();

        gracz.sprawdzCzyPoLosowaniach();
    }
}


class TypyGraczyTest {

    @Test
    void minimalista() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        Minimalista gracz = new Minimalista("Jan", "Kowalski",
                "123456789", 1000, centrala, new Kolektura[]{kolektura});

        gracz.zagraj();

        assertEquals(1, gracz.dajKupony().size());
        assertEquals(700, gracz.dajSrodkiFinansowe());
    }

    @Test
    void losowy() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        Losowy gracz = new Losowy("Jan", "Kowalski",
                "123456789", 1000000, centrala, new Kolektura[]{kolektura});

        gracz.zagraj();

        assertTrue(!gracz.dajKupony().isEmpty() && gracz.dajKupony().size() <= 100);
    }

    @Test
    void staloliczbowy() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        Set<Integer> ulubione = Set.of(1, 2, 3, 4, 5, 6);
        long srodki = 100000;
        Staloliczbowy gracz = new Staloliczbowy("Jan", "Kowalski",
                "123456789", srodki, centrala,
                new Zaklad(ulubione), new Kolektura[]{kolektura});

        gracz.zagraj();

        assertEquals(1, gracz.dajKupony().size());
        long kuponKosztowal = 300L * 10;
        long zostaloSrodkow = srodki - kuponKosztowal;
        assertEquals(zostaloSrodkow, gracz.dajSrodkiFinansowe());
    }

    @Test
    void staloblankietowy() {
        Centrala centrala = new Centrala(new BudzetPanstwa());
        Kolektura kolektura = new Kolektura(centrala);
        Blankiet blankiet = new Blankiet();
        blankiet.skreslKratke(1, 1);
        blankiet.skreslKratke(1, 2);
        blankiet.skreslKratke(1, 3);
        blankiet.skreslKratke(1, 4);
        blankiet.skreslKratke(1, 5);
        blankiet.skreslKratke(1, 6);
        blankiet.skreslLiczbeLosowan(2);

        Staloblankietowy gracz = new Staloblankietowy("Jan", "Kowalski",
                "123456789", 1000, centrala,
                blankiet, 5, new Kolektura[]{kolektura});

        gracz.zagraj();

        assertEquals(1, gracz.dajKupony().size());
        assertEquals(400, gracz.dajSrodkiFinansowe());
    }
}