package totolotek;

public class Staloblankietowy extends Gracz {
    private Blankiet blankiet;
    private int okres;
    private int numerLosowania;

    public Staloblankietowy(String imie, String nazwisko, String pesel,
                         long srodkiFinansowe, Centrala centrala,
                         Blankiet blankiet, int okres, Kolektura[] kolektury) {
        super(imie, nazwisko, pesel, srodkiFinansowe, centrala, kolektury);
        this.blankiet = blankiet;
        this.okres = okres;
        this.numerLosowania = centrala.dajNumerNajblizszegoLosowania();
    }

    @Override
    public void zagraj() {
        if (centrala.dajNumerNajblizszegoLosowania() == numerLosowania) {
            numerLosowania += okres;

            Kolektura kolektura = nastepnaKolektura();
            kolektura.kuponZBlankietu(blankiet, this);
        }
    }
}
