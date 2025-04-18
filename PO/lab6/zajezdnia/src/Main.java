import java.util.Random;
import java.util.Scanner;

public class Main {
    static Random random = new Random();
    static Scanner scanner = new Scanner(System.in);

    private static Autobus losowyAutobus() {
        double szybkoscMaksymalna = random.nextDouble(20,50);
        int numer = random.nextInt(1, 1000);
        double zuzyciePaliwa = random.nextDouble(10, 20);
        return new Autobus(szybkoscMaksymalna, numer, null, zuzyciePaliwa);
    }

    private static Tramwaj losowyTramwaj() {
        double szybkoscMaksymalna = random.nextDouble(20,50);
        int numer = random.nextInt(1, 1000);
        int iloscWagonow = random.nextInt(1, 10);
        return new Tramwaj(szybkoscMaksymalna, numer, null, iloscWagonow);
    }

    private static Pojazd losowyPojazd() {
        double los = random.nextDouble();
        if (los < 0.5) return losowyAutobus();
        else return losowyTramwaj();
    }

    public static void main(String[] args) {
        String nazwaZajezdni;
        int iloscPojazdow;
        System.out.print("Podaj nazwe zajezdni: ");
        nazwaZajezdni = scanner.nextLine();
        System.out.print("Podaj ilosc pojazdow: ");
        iloscPojazdow = scanner.nextInt();

        Zajezdnia zajezdnia = new Zajezdnia(nazwaZajezdni,iloscPojazdow);

        for (int i=0; i<iloscPojazdow; i++) {
            Pojazd pojazd = losowyPojazd();
            pojazd.setZajezdnia(zajezdnia);
            zajezdnia.dodajPojazd(pojazd);
        }

        System.out.println(zajezdnia);
    }
}
