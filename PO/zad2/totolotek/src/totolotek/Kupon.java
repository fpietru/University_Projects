package totolotek;

import java.util.*;

public class Kupon {
    private Kolektura kolektura;
    private String identyfikator;
    private List<Zaklad> zaklady;
    private int liczbaLosowan;
    private int najblizszeLosowanie;
    private long cena;

    public Kupon(Centrala centrala, Kolektura kolektura, List<Zaklad> zaklady, int liczbaLosowan) {
        centrala.nowyWydrukowanyKupon();
        int numerKuponu = centrala.liczbaWydrukowanychKuponow();
        this.kolektura = kolektura;
        this.identyfikator = utworzIdentyfikator(numerKuponu, kolektura.dajNumer());
        this.zaklady = zaklady;
        this.liczbaLosowan = liczbaLosowan;
        this.najblizszeLosowanie = centrala.dajNumerNajblizszegoLosowania();
        this.cena = 300L * zaklady.size() * liczbaLosowan;
    }

    static private int sumaCyfr(int liczba) {
        int wynik = 0;
        while (liczba > 0) {
            wynik += liczba % 10;
            liczba /= 10;
        }
        return wynik;
    }

    static private String utworzIdentyfikator(int numerKuponu, int numerKolektury) {
        Random random = new Random();
        StringBuilder sb = new StringBuilder();
        sb.append(numerKuponu);
        sb.append("-");
        sb.append(numerKolektury);
        sb.append("-");
        int suma = sumaCyfr(numerKuponu) + sumaCyfr(numerKolektury);
        for (int i=1; i<=9; i++) {
            int cyfra = random.nextInt(10);
            suma += cyfra;
            sb.append(cyfra);
        }
        sb.append("-");
        String sformatowane = String.format("%02d", suma % 100);
        sb.append(sformatowane);
        return sb.toString();
    }

    public String dajIdentyfikator() {
        return identyfikator;
    }

    public Kolektura dajKolekture() {
        return kolektura;
    }

    public List<Zaklad> dajZaklady() {
        return zaklady;
    }

    public int dajLiczbeLosowan() {
        return liczbaLosowan;
    }

    public int dajNumerNajblizszegoLosowania() {
        return najblizszeLosowanie;
    }

    public int dajNumerOstatniegoLosowania() {
        return najblizszeLosowanie + liczbaLosowan - 1;
    }

    public boolean bierzeUdzialWLosowaniu(Losowanie losowanie) {
        int nrLosowania = losowanie.dajNumer();
        return (dajNumerNajblizszegoLosowania() <= nrLosowania && nrLosowania <= dajNumerOstatniegoLosowania());
    }

    public int[] zliczWygrane(Losowanie zwycieskie) {
        int[] wynik = new int[5];
        for (int i=0; i<zaklady.size(); i++) {
            Zaklad zaklad = zaklady.get(i);
            int trafione = zwycieskie.porownaj(zaklad);
            if (trafione >= 3) {
                int wygrana = 6 - trafione + 1;
                wynik[wygrana]++;
            }
        }
        return wynik;
    }

    public long dajCene() {
        return cena;
    }

    public long dajPodatek() {
        return (20L * cena) / 100;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("KUPON NR ");
        sb.append(dajIdentyfikator());
        sb.append("\n");
        for (int i=0; i<zaklady.size(); i++) {
            sb.append(i+1);
            sb.append(" ");
            sb.append(zaklady.get(i));
            sb.append("\n");
        }
        sb.append("LICZBA LOSOWAN: ");
        sb.append(liczbaLosowan);
        sb.append("\nNUMERY LOSOWAN: ");
        for (int i=0; i<liczbaLosowan; i++) {
            sb.append(" ");
            sb.append(najblizszeLosowanie + i);
        }
        sb.append("\nCENA: ");
        sb.append(dajCene() / 100L);
        sb.append(" zl ");
        sb.append(dajCene() % 100L);
        sb.append(" gr");
        return sb.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Kupon kupon = (Kupon) o;
        return Objects.equals(identyfikator, kupon.identyfikator);
    }

    @Override
    public int hashCode() {
        return Objects.hash(identyfikator);
    }
}
