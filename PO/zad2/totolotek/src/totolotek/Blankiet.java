package totolotek;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

public class Blankiet {
    boolean[][] kratki;
    boolean[] kratkiLosowan;
    int[] skreslonychWpolu;

    public Blankiet() {
        this.kratki = new boolean[8][50];
        this.kratkiLosowan = new boolean[10];
        this.skreslonychWpolu = new int[8];
    }

    public void skreslKratke(int zaklad, int liczba) {
        sprawdzZaklad(zaklad);
        sprawdzLiczbe(liczba);
        if (!kratki[zaklad-1][liczba-1]) {
            kratki[zaklad-1][liczba-1] = true;
            skreslonychWpolu[zaklad-1]++;
        }
    }

    public void skreslLiczbeLosowan(int liczba) {
        sprawdzLiczbeLosowan(liczba);
        kratkiLosowan[liczba-1] = true;
    }

    public void anulujZaklad(int zaklad) {
        sprawdzZaklad(zaklad);
        kratki[zaklad-1][49] = true;
    }

    public boolean czyAnulowany(int zaklad) {
        sprawdzZaklad(zaklad);
        return kratki[zaklad-1][49];
    }

    public boolean szescSkreslonych(int zaklad) {
        sprawdzZaklad(zaklad);
        return skreslonychWpolu[zaklad-1] == 6;
    }

    public List<Zaklad> dajZaklady() {
        List<Zaklad> zaklady = new ArrayList<>();
        for (int i=1; i<=8; i++) {
            if (!czyAnulowany(i) && szescSkreslonych(i)) {
                Set<Integer> liczby = new TreeSet<>();
                for (int j=1; j<=49; j++) {
                    if (kratki[i-1][j-1]) {
                        liczby.add(j);
                    }
                }
                zaklady.add(new Zaklad(liczby));
            }
        }
        return zaklady;
    }

    public int dajLiczbeLosowan() {
        int liczbaLosowan = 1;
        for (int i=10; i>=1; i--) {
            if (kratkiLosowan[i-1]) {
                liczbaLosowan = i;
                break;
            }
        }
        return liczbaLosowan;
    }

    private static void sprawdzLiczbe(int liczba) {
        if (liczba < 1 || liczba > 49) {
            throw  new IllegalArgumentException("Liczba jest z przedzialu [1, 49]");
        }
    }

    private static void sprawdzZaklad(int zaklad) {
        if (zaklad < 1 || zaklad > 8) {
            throw new IllegalArgumentException("Zaklad ma wartosc z przedzialu [1, 8]");
        }
    }

    private static void sprawdzLiczbeLosowan(int liczbaLosowan) {
        if (liczbaLosowan < 1 || liczbaLosowan > 10) {
            throw new IllegalArgumentException("Liczba Losowan jest z przedzialu [1, 10]");
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i=1; i<=8; i++) {
            sb.append(i);
            sb.append(":\n");
            for (int j=1; j<=49; j++) {
                if (kratki[i-1][j-1]) {
                    sb.append(" [ -- ] ");
                } else {
                    sb.append(String.format(" [ %2d ] ", j));
                }
                if (j % 10 == 0 || j == 49) {
                    sb.append("\n");
                }
            }
            sb.append(" [    ] anuluj\n");
        }

        sb.append("Liczba losowan: ");
        for (int i=1; i<=10; i++) {
            if (kratkiLosowan[i - 1]) {
                sb.append(" [ -- ] ");
            } else {
                sb.append(String.format(" [ %d ] ", i));
            }
        }

        return sb.toString();
    }
}
