public class Szkola {
    private String nazwa;
    private Klasa[] klasy;

    public Szkola(String nazwa, Klasa[] klasy) {
        this.nazwa = nazwa;
        this.klasy = klasy;
    }

    public String getNazwa() {
        return nazwa;
    }

    public Klasa[] getKlasy() {
        return klasy;
    }
}
