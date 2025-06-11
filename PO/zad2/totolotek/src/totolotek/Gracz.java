package totolotek;

import java.util.ArrayList;
import java.util.List;

public abstract class Gracz {
    protected String imie;
    protected String nazwisko;
    protected String pesel;
    protected long srodkiFinansowe;
    protected List<Kupon> kupony;
    protected Centrala centrala;
    protected Kolektura[] kolektury;
    protected int indeksKolektury;

    public Gracz(String imie, String nazwisko, String pesel,
                 long srodkiFinansowe, Centrala centrala, Kolektura[] kolektury) {
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.pesel = pesel;
        this.srodkiFinansowe = srodkiFinansowe;
        this.kupony = new ArrayList<>();
        this.centrala = centrala;
        this.kolektury = kolektury;
        this.indeksKolektury = 0;
    }

    public abstract void zagraj();

    public void przyjmijKupon(Kupon kupon) {
        kupony.add(kupon);
    }

    public List<Kupon> dajKupony() {
        return kupony;
    }

    public long dajSrodkiFinansowe() {
        return srodkiFinansowe;
    }

    public void zmniejszSrodkiFinansowe(long kwota) {
        srodkiFinansowe -= kwota;
    }

    public void zwiekszSrodkiFinansowe(long kwota) {
        srodkiFinansowe += kwota;
    }

    protected Kolektura nastepnaKolektura() {
        int indeks = indeksKolektury;
        indeksKolektury = (indeksKolektury + 1) % kolektury.length;
        return kolektury[indeks];
    }

    public void odbierzWygrana(Kupon kupon) {
        Kolektura kolektura = kupon.dajKolekture();
        kolektura.wyplacWygrana(this, kupon);
    }

    public void sprawdzCzyPoLosowaniach() {
        int nrNajblizszegoLos = centrala.dajNumerNajblizszegoLosowania();
        for (Kupon kupon : kupony) {
            int nrOstatniegoLosZKuponu = kupon.dajNumerOstatniegoLosowania();
            if (nrNajblizszegoLos > nrOstatniegoLosZKuponu) {
                odbierzWygrana(kupon);
            }
        }
    }

    public void odbierzIleSieDa() {
        for (Kupon kupon : kupony) {
            odbierzWygrana(kupon);
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("\nImie: ");
        sb.append(imie);
        sb.append("\nNazwisko: ");
        sb.append(nazwisko);
        sb.append("\nPESEL: ");
        sb.append(pesel);
        sb.append("\nPosiadane Srodki:");
        sb.append(srodkiFinansowe);
        if (kupony.isEmpty()) {
            sb.append("\nNie posiada kuponow\n");
        } else {
            sb.append("\nLista identyfikatorow posiadanych kuponow:\n");
            for (Kupon kupon : kupony) {
                sb.append(kupon.dajIdentyfikator());
                sb.append("\n");
            }
        }
        return sb.toString();
    }
}
