package Wybory;

public class Kandydat {
    private String nazwisko;
    private Komitet komitet;
    private int liczbaGlosow;
    private boolean mandat = false;


    public Kandydat(String nazwisko, int liczbaGlosow) {
        this.nazwisko = nazwisko;
        this.liczbaGlosow = liczbaGlosow;
    }

    public void setKomitet(Komitet komitet) {
        this.komitet = komitet;
    }

    public void przyznajMandat() {
        mandat = true;
    }

    public boolean maMandat() {
        return mandat;
    }

    public String getNazwisko() {
        return nazwisko;
    }

    public int getLiczbaGlosow() {
        return liczbaGlosow;
    }
}
