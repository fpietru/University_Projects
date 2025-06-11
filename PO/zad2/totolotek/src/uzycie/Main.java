package uzycie;

import totolotek.*;

import java.util.Random;

public class Main {

    public static void prezentacjaDzialania() {
        BudzetPanstwa budzetPanstwa = new BudzetPanstwa();

        Centrala centrala = new Centrala(budzetPanstwa);

        Kolektura[] kolektury = new Kolektura[10];
        for (int i=0; i<10; i++) {
            kolektury[i] = new Kolektura(centrala);
        }

        Random random = new Random();

        // gracze minimalisci
        int liczbaGraczy = 200;
        long srodkiFinansowe;
        long milion = 100000000; // zl, groszy to 10^8
        Minimalista[] minimalisci = new Minimalista[liczbaGraczy];
        for (int i=0; i<liczbaGraczy; i++) {
            String imie = "Minimalista nr " + i;
            String nazwisko = "Kowalski";
            String pesel = "P" + i;
            srodkiFinansowe = random.nextLong(milion);
            Kolektura[] kolekturyGracza = new Kolektura[1];
            kolekturyGracza[0] = kolektury[i % 10];
            minimalisci[i] = new Minimalista(imie, nazwisko,
                    pesel, srodkiFinansowe, centrala, kolekturyGracza);
        }

        // gracze losowi
        Losowy[] losowi = new Losowy[liczbaGraczy];
        for (int i=0; i<liczbaGraczy; i++) {
            String imie = "Losowy nr " + i;
            String nazwisko = "Kowalski";
            String pesel = "P" + i;
            srodkiFinansowe = random.nextLong(milion);
            Kolektura[] kolekturyGracza = new Kolektura[1];
            kolekturyGracza[0] = kolektury[i % 10];
            losowi[i] = new Losowy(imie, nazwisko,
                    pesel, srodkiFinansowe, centrala, kolekturyGracza);
        }

        // gracze staloblankietowi
        Staloblankietowy[] staloblankietowi = new Staloblankietowy[liczbaGraczy];
        for (int i=0; i<liczbaGraczy; i++) {
            String imie = "Staloblankietowy nr " + i;
            String nazwisko = "Kowalski";
            String pesel = "P" + i;
            srodkiFinansowe = random.nextLong(milion);
            int okres = random.nextInt(10) + 1;
            Blankiet blankiet = new Blankiet();
            blankiet.skreslKratke(1, 1);
            blankiet.skreslKratke(1, 2);
            blankiet.skreslKratke(1, 3);
            blankiet.skreslKratke(1, 5);
            blankiet.skreslKratke(1, 8);
            blankiet.skreslKratke(1, 13);
            blankiet.skreslLiczbeLosowan(random.nextInt(10)+1);
            staloblankietowi[i] = new Staloblankietowy(imie, nazwisko,
                    pesel, srodkiFinansowe, centrala, blankiet, okres, kolektury);
        }

        // gracze staloliczbowi
        Staloliczbowy[] staloliczbowi = new Staloliczbowy[liczbaGraczy];
        for (int i=0; i<liczbaGraczy; i++) {
            String imie = "Staloliczbowy nr " + i;
            String nazwisko = "Kowalski";
            String pesel = "P" + i;
            srodkiFinansowe = random.nextLong(milion);
            Zaklad zaklad = new Zaklad();
            staloliczbowi[i] = new Staloliczbowy(imie, nazwisko,
                    pesel, srodkiFinansowe, centrala, zaklad, kolektury);
        }


        // przeprowadzam 20 losowan
        int liczbaLosowan = 20;
        for (int i=0; i<liczbaLosowan; i++) {
            // gracze graja
            for (int j=0; j<liczbaGraczy; j++) {
                minimalisci[j].zagraj();
                losowi[j].zagraj();
                staloblankietowi[j].zagraj();
                staloliczbowi[j].zagraj();
            }
            centrala.przeprowadzLosowanie();
            // gracze odbieraja wygrane
            for (int j=0; j<liczbaGraczy; j++) {
                minimalisci[j].sprawdzCzyPoLosowaniach();
                losowi[j].sprawdzCzyPoLosowaniach();
                staloblankietowi[j].sprawdzCzyPoLosowaniach();
                staloliczbowi[j].sprawdzCzyPoLosowaniach();
            }
        }

        // wypisuje najwazniejsze informacje
        System.out.println(centrala);
        System.out.println(budzetPanstwa);
    }




    public static void main(String[] args) {
        prezentacjaDzialania();
    }
}
