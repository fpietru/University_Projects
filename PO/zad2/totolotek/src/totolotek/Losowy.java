package totolotek;

import java.util.Random;

public class Losowy extends Gracz {
    Random random = new Random();
    public Losowy(String imie, String nazwisko, String pesel
                  ,long srodkiFinansowe, Centrala centrala, Kolektura[] kolektury) {
        super(imie, nazwisko, pesel, srodkiFinansowe, centrala, kolektury);
        long milion = 100000000;
        this.srodkiFinansowe = random.nextLong(milion);
    }

    @Override
    public void zagraj() {
        int liczbaKuponow = random.nextInt(100) + 1;
        for (int i=1; i<=liczbaKuponow; i++) {
            int liczbaZakladow = random.nextInt(8) + 1;
            int liczbaLosowan = random.nextInt(10) + 1;

            Kolektura kolektura = centrala.losowaKolektura();
            kolektura.kuponNaChybilTrafil(liczbaZakladow, liczbaLosowan, this);
        }
    }
}
