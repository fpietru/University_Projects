import java.util.Arrays;

public class Kuratorium {
    private Zyczenie[] listaZyczen;
    private Szkola[] szkoly;
    private Uczen[] uczniowie;
    private Uczen[] nieprzyjeci;
    private int liczbaNieprzyjetych;

    public Kuratorium(Zyczenie[] listaZyczen, Szkola[] szkoly, Uczen[] uczniowie) {
        this.listaZyczen = listaZyczen;
        this.szkoly = szkoly;
        this.uczniowie = uczniowie;
        this.nieprzyjeci = new Uczen[uczniowie.length];
        this.liczbaNieprzyjetych = 0;
    }

    public void algorytmPrzydzialu() {
        Arrays.sort(listaZyczen);
        for (int i=0; i< listaZyczen.length; i++) {
            listaZyczen[i].setPozycja(i);
        }
        for (Zyczenie z : listaZyczen) {
            rozpatrzZyczenie(z);
        }
        for (Uczen u : uczniowie) {
            if (u.getSpelnione() == null) {
                nieprzyjeci[liczbaNieprzyjetych++] = u;
            }
        }
    }

    private void rozpatrzZyczenie(Zyczenie z) {
        Uczen u = z.getUczen();
        if (z.getStatus() != Zyczenie.NIEWIADOMO) return;

        if (!z.getKlasa().czyWolne()) {
            z.setStatus(Zyczenie.ODRZUCONE);
            return;
        }

        Zyczenie aktualne = u.getSpelnione();
        if (aktualne == null) {
            zaakceptuj(z);
        } else if (z.getNumer() > aktualne.getNumer()) {
            z.setStatus(Zyczenie.ODRZUCONE);
        } else {
            int pozycjaCofnietego = aktualne.getPozycja();
            aktualne.setStatus(Zyczenie.ODRZUCONE);
            aktualne.getKlasa().usunUcznia(u);
            zaakceptuj(z);
            if (pozycjaCofnietego < z.getPozycja()) {
                for (int i = pozycjaCofnietego + 1; i < listaZyczen.length; i++) {
                    rozpatrzZyczenie(listaZyczen[i]);
                }
            }
        }
    }

    private void zaakceptuj(Zyczenie z) {
        z.setStatus((Zyczenie.PRZYJETE));
        z.getKlasa().dodajUcznia(z.getUczen());
        z.getUczen().setSpelnione(z);
    }

    public Uczen[] getNieprzyjeci() { return nieprzyjeci; }
}
