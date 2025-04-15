package przyklad;
import wyrazenia.Stala;
import wyrazenia.Wyrazenie;

public class Main {
    public static void main(String[] args) {
        Wyrazenie s2 = new Stala(2);
        System.out.println("Wartosc " + s2 + "w punkcie 0 to " + s2.wartosc(0));
        System.out.println("Calka od 0 do 4 to " + s2.calkaOzn(0, 4));
    }

}
