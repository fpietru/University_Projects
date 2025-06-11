package totolotek;

public class Staloliczbowy extends Gracz {
    private Zaklad zaklad;

    public Staloliczbowy(String imie, String nazwisko, String pesel,
                         long srodkiFinansowe, Centrala centrala,
                         Zaklad zaklad, Kolektura[] kolektury) {
        super(imie, nazwisko, pesel, srodkiFinansowe, centrala, kolektury);
        this.zaklad = zaklad;
    }

    @Override
    public void zagraj() {

        int ostatnieLosowanie = 0;
        if (!kupony.isEmpty()) {
            ostatnieLosowanie = kupony.getLast().dajNumerOstatniegoLosowania();
        }

        if (centrala.dajNumerNajblizszegoLosowania() > ostatnieLosowanie) {
            Blankiet blankiet = new Blankiet();
            for (int liczba : zaklad.dajLiczby()) {
                blankiet.skreslKratke(1, liczba);
            }
            blankiet.skreslLiczbeLosowan(10);
            Kolektura kolektura = nastepnaKolektura();
            kolektura.kuponZBlankietu(blankiet, this);
        }
    }
}
