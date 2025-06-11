package totolotek;

import java.util.*;

public class Kolektura {
    private Centrala centrala;
    private Set<Kupon> sprzedaneKupony;
    private Set<Kupon> zrealizowaneKupony;
    private int numer;

    public Kolektura(Centrala centrala) {
        centrala.nowaKolektura(this);
        this.centrala = centrala;
        this.numer = centrala.liczbaKolektor();
        this.sprzedaneKupony = new HashSet<>();
        this.zrealizowaneKupony = new HashSet<>();
    }

    // zwraca true jesli transakcja udana
    public boolean transakcja(Gracz klient, int liczbaZakladow, int liczbaLosowan) {
        long cenaKuponu = 300L * liczbaZakladow * liczbaLosowan;
        long dlaKazdegoLosowania = cenaKuponu / liczbaLosowan;
        if (klient.dajSrodkiFinansowe() >= cenaKuponu) {
            klient.zmniejszSrodkiFinansowe(cenaKuponu);
            int ostatnieLosowanie = centrala.dajNumerNajblizszegoLosowania() + liczbaLosowan - 1;
            for (int l = centrala.dajNumerNajblizszegoLosowania(); l<=ostatnieLosowanie; l++) {
                centrala.przyjmijPrzychod(l, dlaKazdegoLosowania);
            }
            return true;
        }
        return false;
    }

    public void kuponZBlankietu(Blankiet blankiet, Gracz klient) {
        List<Zaklad> zaklady = blankiet.dajZaklady();
        int liczbaLosowan = blankiet.dajLiczbeLosowan();
        if (zaklady.isEmpty()) {
            return;
        }
        if (transakcja(klient, zaklady.size(), liczbaLosowan)) {
            Kupon kupon = new Kupon(centrala, this, zaklady, liczbaLosowan);
            centrala.dodajKupionyKupon(kupon);
            klient.przyjmijKupon(kupon);
            sprzedaneKupony.add(kupon);
        }
    }

    public void kuponNaChybilTrafil(int liczbaZakladow, int liczbaLosowan, Gracz klient) {
        if (liczbaZakladow < 0 || liczbaZakladow > 8) {
            throw new IllegalArgumentException("Kupon moze zawierac od 1 do 8 zakladow");
        }
        if (liczbaLosowan > 10) {
            throw new IllegalArgumentException("Kupon moze byc zawarty na co najwyzej 10 kolejnych losowan");
        }
        if (transakcja(klient, liczbaZakladow, liczbaLosowan)) {
            // tworze losowe zaklady
            List<Zaklad> zaklady = new ArrayList<>();
            for (int i=0; i<liczbaZakladow; i++) {
                zaklady.add(new Zaklad());
            }
            Kupon kupon = new Kupon(centrala, this, zaklady, liczbaLosowan);
            centrala.dodajKupionyKupon(kupon);
            klient.przyjmijKupon(kupon);
            sprzedaneKupony.add(kupon);
        }
    }

    public int dajNumer() {
        return numer;
    }

    public void wyplacWygrana(Gracz klient, Kupon kupon) {
        boolean wTejKolekturze = sprzedaneKupony.contains(kupon);
        boolean nieZrealizowany = !zrealizowaneKupony.contains(kupon);

        long wysokie = 2280L * 100;
        long sumaNagrod = 0L;

        if (wTejKolekturze && nieZrealizowany) {
            zrealizowaneKupony.add(kupon);
            for (int i = kupon.dajNumerNajblizszegoLosowania(); i<=kupon.dajNumerOstatniegoLosowania(); i++) {
                if (i >= centrala.dajNumerNajblizszegoLosowania()) {
                    break;
                }

                Losowanie losowanie = centrala.dajLosowanie(i);
                int[] ileWygrany = kupon.zliczWygrane(losowanie);
                for (int j=1; j<=4; j++) {
                    long kwotaWygranejStJ = centrala.dajKwoteWygranej(i, j);
                    kwotaWygranejStJ *= ileWygrany[j];

                    if (kwotaWygranejStJ >= wysokie) {
                        long podatek = (10L * kwotaWygranejStJ) / 100;
                        centrala.przekazPodatek(podatek);
                        kwotaWygranejStJ -= podatek;
                    }
                    sumaNagrod += kwotaWygranejStJ;
                }

                klient.zwiekszSrodkiFinansowe(centrala.pokryjKoszt(sumaNagrod));
            }
        }
    }

}
