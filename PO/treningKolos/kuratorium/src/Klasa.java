public class Klasa {
    private Szkola szkola;
    private String profil;
    private int limit;
    private int wolne;
    private int liczbaUczniow;
    private Uczen[] uczniowie;

    public Klasa(Szkola szkola, String profil, int limit) {
        this.szkola = szkola;
        this.profil = profil;
        this.limit = limit;
        this.wolne = limit;
        this.liczbaUczniow = 0;
        this.uczniowie = new Uczen[limit];
    }

    public int getWolne() { return wolne; }
    public boolean czyWolne() { return wolne > 0; }
    public void decWolne() { if (wolne > 0) { wolne--; } }
    public void incWolne() { wolne++; }

    public void dodajUcznia(Uczen uczen) {
        if (czyWolne()) {
            uczniowie[liczbaUczniow++] = uczen;
            decWolne();
        }
    }

    public void usunUcznia(Uczen uczen) {
        for (int i=0; i<liczbaUczniow; i++) {
            if (uczniowie[i] == uczen) {
                for (int j=i; j<liczbaUczniow-1; j++) {
                    uczniowie[j] = uczniowie[j+1];
                }
                liczbaUczniow--;
                incWolne();
                break;
            }
        }
    }
}
