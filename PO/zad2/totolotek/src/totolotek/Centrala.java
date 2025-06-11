package totolotek;

import java.util.*;

import static java.lang.Long.max;

public class Centrala {
    private BudzetPanstwa budzetPanstwa;
    private long kumulacja;
    private long sumaSrodkow;
    private int wydrukowaneKupony;
    private List<Losowanie> losowania;
    private List<Kolektura> kolektury;
    private List<Kupon> kupioneKupony;
    private HashMap<Integer, Long> srodkiFinansowe;
    private HashMap<Integer, Long[]> nagrodyDlaLosowania;
    private HashMap<Integer, Long[]> kwotyWygranejDlaLosowania;
    private HashMap<Integer, Integer[]> liczbyZwyciezcow;

    public Centrala(BudzetPanstwa budzetPanstwa) {
        this.budzetPanstwa = budzetPanstwa;
        this.kumulacja = 0;
        this.sumaSrodkow = 0;
        this.wydrukowaneKupony = 0;
        this.losowania = new ArrayList<>();
        this.kolektury = new ArrayList<>();
        this.kupioneKupony = new ArrayList<>();
        this.srodkiFinansowe = new HashMap<>();
        this.nagrodyDlaLosowania = new HashMap<>();
        this.kwotyWygranejDlaLosowania = new HashMap<>();
        this.liczbyZwyciezcow = new HashMap<>();
    }

    public void nowaKolektura(Kolektura kolektura) {
        kolektury.add(kolektura);
    }

    public int liczbaKolektor() {
        return kolektury.size();
    }

    public Kolektura losowaKolektura() {
        if (kolektury.isEmpty()) {
            throw new RuntimeException("Centrala zawsze ma choc jedna kolekture");
        }
        Random random = new Random();
        int randomIndeks = random.nextInt(kolektury.size());
        return kolektury.get(randomIndeks);
    }

    public void dodajKupionyKupon(Kupon kupon) {
        kupioneKupony.add(kupon);
    }

    public void nowyWydrukowanyKupon() {
        wydrukowaneKupony++;
    }

    public int liczbaWydrukowanychKuponow() {
        return wydrukowaneKupony;
    }

    private void noweLosowanie(Zaklad zaklad) {
        int numer = losowania.size() + 1;
        losowania.add(new Losowanie(numer, zaklad));
    }

    public int liczbaLosowan() {
        return losowania.size();
    }

    public Losowanie dajLosowanie(int nrLosowania) {
        return losowania.get(nrLosowania - 1);
    }

    // najblizsze NIEPRZEPROWADZONE losowanie
    public int dajNumerNajblizszegoLosowania() {
        return liczbaLosowan() + 1;
    }

    public void przekazPodatek(long kwota) {
        budzetPanstwa.zbierzPodatek(kwota);
    }

    public void przyjmijPrzychod(int nrLosowania, long kwotaBrutto) {
        long podatek = (20L * kwotaBrutto) / 100;
        long kwotaNetto = kwotaBrutto - podatek;
        srodkiFinansowe.put(nrLosowania, srodkiFinansowe.getOrDefault(nrLosowania, 0L) + kwotaNetto);
        przekazPodatek(podatek);
    }

    public long pokryjKoszt(long kwota) {
        if (kwota > sumaSrodkow) {
            long roznica = kwota - sumaSrodkow;
            sumaSrodkow += budzetPanstwa.przekazSubwencje(roznica);
        }
        sumaSrodkow -= kwota;
        return kwota;
    }

    public void przeprowadzLosowanie() {
        przeprowadzLosowanie(new Zaklad()); // losowy zwycieski zaklad
    }

    public void przeprowadzLosowanie(Zaklad zwycieskiZaklad) {
        noweLosowanie(zwycieskiZaklad);

        Losowanie losowanie = losowania.getLast();
        int nrLosowania = losowanie.dajNumer();

        // zliczam zwyciezcow kazdego stopnia
        Integer[] zlicz = new Integer[]{0, 0, 0, 0, 0};
        for (Kupon kupon : kupioneKupony) {
            // System.out.println(kupon);
            if (kupon.bierzeUdzialWLosowaniu(losowanie)) {
                int[] wygraneKuponu = kupon.zliczWygrane(losowanie);
                for (int i = 1; i <= 4; i++) {
                    zlicz[i] += wygraneKuponu[i];
                }
            }
        }

        // zapisuje liczbe zwyciezcow dla tego losowania
        liczbyZwyciezcow.put(nrLosowania, zlicz);

        // wyliczam pule nagrod kazdego stopnia
        long srodkiPoLosowaniu = srodkiFinansowe.get(nrLosowania);

        long kwotaNaNagrody = (51L * srodkiPoLosowaniu) / 100;
        long zyskPoLosowaniu = srodkiPoLosowaniu - kwotaNaNagrody;
        Long[] nagrody = new Long[]{0L, 0L, 0L, 0L, 0L};
        nagrody[1] = (44L * kwotaNaNagrody) / 100;
        nagrody[2] = (8L * kwotaNaNagrody) / 100;
        nagrody[4] = pokryjKoszt(2400L * zlicz[4]);
        nagrody[3] = max(0L, kwotaNaNagrody - (nagrody[1] + nagrody[2] + nagrody[4]));

        // gwarantowana dla 1 stopnia
        long dwaMiliony = 200000000L;
        if (nagrody[1] < dwaMiliony) {
            long roznica = dwaMiliony - nagrody[1];
            nagrody[1] += pokryjKoszt(roznica);
        }
        nagrody[1] += kumulacja;
        kumulacja = 0L;

        // gwarantowana dla 3 stopnia
        long minDlaTrzeciegoSt = 3600L * zlicz[3];
        if (nagrody[3] < minDlaTrzeciegoSt) {
            long roznica = minDlaTrzeciegoSt - nagrody[3];
            nagrody[3] += pokryjKoszt(roznica);
        }

        Long[] kwoty = new Long[]{0L, 0L, 0L, 0L, 0L};

        // dziele nagrody przez liczbe zwycieskich kuponow (jesli takie sa)
        for (int i = 1; i <= 4; i++) {
            if (zlicz[i] >= 1L) {
                kwoty[i] = nagrody[i] / zlicz[i];
            }
        }

        // pule nagrod przelewam do sumySrodkow
        // potem to z niej kolektury wyplacaja wygrane graczy
        sumaSrodkow += zyskPoLosowaniu;
        for (int i=1; i<=4; i++) {
            sumaSrodkow += nagrody[i];
        }

        // wyliczam kumulacje
        if (zlicz[1] == 0) {
            kumulacja = nagrody[1];
        }

        // zapisuje pule nagrod i kwoty dla tego losowania
        nagrodyDlaLosowania.put(nrLosowania, nagrody);
        kwotyWygranejDlaLosowania.put(nrLosowania, kwoty);
    }

    public long dajKumulacje() {
        return kumulacja;
    }

    public long dajSumeSrodkow() {
        return sumaSrodkow;
    }

    public long dajSrodkiFinansowe(int nrLosowania) {
        return srodkiFinansowe.get(nrLosowania);
    }

    public Long[] dajNagrodyDlaLosowania(int nrLosowania) {
        return nagrodyDlaLosowania.get(nrLosowania);
    }

    public long dajKwoteWygranej(int nrLosowania, int stopien) {
        return kwotyWygranejDlaLosowania.get(nrLosowania)[stopien];
    }

    public String wypiszWynikiLosowania(Losowanie losowanie) {
        StringBuilder sb = new StringBuilder();
        sb.append(losowanie);
        int nrLosowania = losowanie.dajNumer();
        Long[] nagrody = nagrodyDlaLosowania.get(nrLosowania);
        sb.append("\nPULE NAGROD:\n");
        for (int i = 1; i <= 4; i++) {
            sb.append(i);
            sb.append(": ");
            sb.append(nagrody[i] / 100L);
            sb.append(" zl ");
            sb.append(nagrody[i] % 100L);
            sb.append(" gr\n");
        }
        Long[] kwoty = kwotyWygranejDlaLosowania.get(nrLosowania);
        Integer[] liczbaZwyciezcow = liczbyZwyciezcow.get(nrLosowania);
        sb.append("KWOTY WYGRANYCH:\n");
        for (int i = 1; i <= 4; i++) {
            sb.append(i);
            sb.append(": ");
            sb.append(kwoty[i] / 100L);
            sb.append(" zl ");
            sb.append(kwoty[i] % 100L);
            sb.append(" gr\n");
            sb.append("Liczba zwyciezcow: ");
            sb.append(liczbaZwyciezcow[i]);
            sb.append("\n");
        }
        return sb.toString();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("CENTRALA:\n");
        for (Losowanie losowanie : losowania)
            sb.append(wypiszWynikiLosowania(losowanie));
        sb.append("Stan Srodkow finansowych: ");
        sb.append(sumaSrodkow / 100L);
        sb.append(" zl ");
        sb.append(sumaSrodkow % 100L);
        sb.append(" gr");
        return sb.toString();
    }
}
