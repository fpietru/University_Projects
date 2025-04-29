package Przyklad;

import Wybory.Kandydat;
import Wybory.Komisja;
import Wybory.Komitet;

public class main {
    public static void main(String[] args) {

        Kandydat[] kandydaci1 = {
                new Kandydat("Nowak", 300),
                new Kandydat("Kowalski", 250),
                new Kandydat("Wisniewski", 170)
        };

        // Kandydaci komitetu 2
        Kandydat[] kandydaci2 = {
                new Kandydat("Zielinski", 100),
                new Kandydat("Kaczmarek", 100),
                new Kandydat("Mazur", 100)
        };

        // Kandydaci komitetu 3
        Kandydat[] kandydaci3 = {
                new Kandydat("Lewandowski", 280),
                new Kandydat("Wojcik", 120),
                new Kandydat("Kaminski", 80)
        };

        // Komitety
        Komitet komitet1 = new Komitet("Wolna Bajtocja", kandydaci1);         // suma 720
        Komitet komitet2 = new Komitet("Bajtek i przyjaciele", kandydaci2);   // suma 400
        Komitet komitet3 = new Komitet("Precz z kompilacją", kandydaci3);     // suma 480

        Komitet[] komitety = { komitet1, komitet2, komitet3 };

        // Komisja i podział mandatów
        Komisja komisja = new Komisja();
        komisja.przydzielMandaty(komitety, 8, 5.0); // 8 mandatów, próg 5%

        // Wyświetlenie wyników
        for (Komitet k : komitety) {
            System.out.println("Komitet: " + k.getNazwa());
            if (k.getZdobywcyMandatow() != null) {
                for (Kandydat kand : k.getZdobywcyMandatow()) {
                    System.out.println("  Mandat: " + kand.getNazwisko() + " (" + kand.getLiczbaGlosow() + " głosów)");
                }
            } else {
                System.out.println("  Brak mandatów.");
            }
        }
    }
}
