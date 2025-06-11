package totolotek;

public class Minimalista extends Gracz {
    public Minimalista(String imie, String nazwisko, String pesel,
                       long srodkiFinansowe, Centrala centrala, Kolektura[] kolektury) {
        super(imie, nazwisko, pesel, srodkiFinansowe, centrala, kolektury);
        if (kolektury.length != 1) {
            throw new IllegalArgumentException("Minimalista ma tylko jedna ulubiona kolekture");
        }
    }

    @Override
    public void zagraj() {
        Kolektura kolektura = nastepnaKolektura();
        kolektura.kuponNaChybilTrafil(1, 1, this);
    }

}
