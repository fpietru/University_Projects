package przyklad;
import wyrazenia.Iloczyn;
import wyrazenia.Stala;
import wyrazenia.Wyrazenie;
import wyrazenia.Zmienna;

public class Main {
    public static void main(String[] args) {
        Wyrazenie s2 = new Stala(2);
        System.out.println("Wartosc " + s2 +
                " w punkcie 0 to " + s2.wartosc(0));
        System.out.println("Calka od 0 do 4 to " +
                s2.calkaOzn(0, 4));

        Wyrazenie x42 = Zmienna.dajInstancje()
                .dodaj(new Stala(42));
        System.out.println("Wartosc " + x42 +
                " w punkcie 12 to " + x42.wartosc(12));

        System.out.println("Pochodna " + x42 +
                " to " + x42.pochodna());
        Wyrazenie x2 = new Iloczyn(
                Zmienna.dajInstancje(),
                new Stala(2));

    }
}
