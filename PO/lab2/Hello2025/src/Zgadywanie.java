import java.util.Random;
import java.util.Scanner;

public class Zgadywanie {

    void graj() {
        int strzal = -1;
        Random rand = new Random();
        Scanner scan = new Scanner(System.in);
        int zagadka = rand.nextInt(1, 10);
        do {
            System.out.println("Try: ");
            strzal = Integer.parseInt(scan.nextLine());
        } while (strzal != zagadka);
        System.out.println("Congratulations!");
    }
}
