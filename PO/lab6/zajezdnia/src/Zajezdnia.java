public class Zajezdnia {
    private String nazwa;
    private int iloscPojazdow;
    private int obecnaIloscPojadow;
    private Pojazd[] pojazdy;

    Zajezdnia(String nazwa, int iloscPojazdow) {
        this.nazwa = nazwa;
        this.iloscPojazdow = iloscPojazdow;
        this.pojazdy = new Pojazd[iloscPojazdow];
        this.obecnaIloscPojadow = 0;
    }

    public void dodajPojazd(Pojazd pojazd) {
        if (obecnaIloscPojadow + 1 > iloscPojazdow) {
            return;
        } else {
            pojazdy[obecnaIloscPojadow++] = pojazd;
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Zajezdnia \"").append(nazwa).append("\":\n");

        for (int i=0; i<obecnaIloscPojadow; i++) {
            sb.append(pojazdy[i].toString());
        }
        return sb.toString();
    }
}
