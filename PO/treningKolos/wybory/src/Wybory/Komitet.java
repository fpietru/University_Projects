package Wybory;

public class Komitet {
    private String nazwa;
    private Kandydat[] kandydaci;
    private Kandydat[] zdobywcyMandatow;
    private int sumaGlosow;

    public Komitet(String nazwa, Kandydat[] kandydaci) {
        this.nazwa = nazwa;
        this.kandydaci = kandydaci;
        this.sumaGlosow = obliczSumeGlosow();
    }

    private int obliczSumeGlosow() {
        int suma = 0;
        for (Kandydat k : kandydaci) {
            suma += k.getLiczbaGlosow();
        }
        return suma;
    }

    public String getNazwa() {
        return nazwa;
    }

    public int getSumaGlosow() {
        return sumaGlosow;
    }

    public Kandydat[] getKandydaci() {
        return kandydaci;
    }

    public int ileKandydatow() {
        return kandydaci.length;
    }

    public Kandydat[] getZdobywcyMandatow() {
        return zdobywcyMandatow;
    }

    public void setZdobywcyMandatow(Kandydat[] zdobywcyMandatow) {
        this.zdobywcyMandatow = zdobywcyMandatow;
    }

    public void modyfikujZdobywcow(int pozycja, Kandydat kandydat) {
        zdobywcyMandatow[pozycja] = kandydat;
    }
}
