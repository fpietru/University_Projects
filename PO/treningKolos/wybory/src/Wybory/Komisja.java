package Wybory;

import java.util.Arrays;

import static java.lang.Math.min;

public class Komisja {

    public void przydzielMandaty(Komitet[] komitety, int liczbaMandatow, double progProcentowy) {
        // krok 1
        int sumaWszystkichGlosow = 0;
        for (Komitet k : komitety) {
            sumaWszystkichGlosow += k.getSumaGlosow();
        }

        // krok 2
        int ileZakw = 0;
        Komitet[] zakwalifikowani = new Komitet[komitety.length];
        for (Komitet k : komitety) {
            if (k.getSumaGlosow() >= sumaWszystkichGlosow * (progProcentowy / 100.0)) {
                zakwalifikowani[ileZakw++] = k;
            }
        }

        // krok 3
        Iloraz[] ilorazy = new Iloraz[liczbaMandatow * ileZakw];
        int ileIlo = 0;
        for (Komitet k : zakwalifikowani) {
            for (int j=1; j<=liczbaMandatow; j++) {
                double wartosc = (double) k.getSumaGlosow() / j;
                ilorazy[ileIlo++] = new Iloraz(wartosc, k);
            }
        }

        // krok 4
        Arrays.sort(ilorazy);
        int[] mandaty = new int[ileZakw];

        for (int i=0; i<liczbaMandatow; i++) {
            Komitet k = ilorazy[i].getKomitet();
            for (int j=0; j<ileZakw; j++) {
                if (zakwalifikowani[j] == k) {
                    mandaty[j]++;
                    break;
                }
            }
        }

        // krok 5
        for (int i=0; i<ileZakw; i++) {
            Komitet k = zakwalifikowani[i];
            Kandydat[] kopia = Arrays.copyOf(k.getKandydaci(), k.getKandydaci().length);
            Arrays.sort(kopia, (a, b) -> b.getLiczbaGlosow() - a.getLiczbaGlosow());
            k.setZdobywcyMandatow(new Kandydat[min(mandaty[i], k.ileKandydatow())]);
            for (int j=0; j<mandaty[i]; j++) {
                if (j < k.ileKandydatow()) {
                    kopia[j].przyznajMandat();
                    k.modyfikujZdobywcow(j, kopia[j]);
                }
            }
        }
    }

}
