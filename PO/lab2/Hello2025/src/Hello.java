import java.util.Random;
import java.util.Scanner;

public class Hello {

    /**
     * Wypisuje hello world i argumenty
     * @param args lista argumentow programu
     */
    public static void printHelloAndArgs(String[] args) {
        System.out.println("Hello World!");
        for (String arg : args) {
            System.out.println(arg);
        }
    }

    public static void main(String[] args) {
        printHelloAndArgs(args);

        Zgadywanie zgadywanie = new Zgadywanie();
        zgadywanie.graj();

        int x = 0;
        Integer x2 = 0;

        double d = 0.0;
        Double d2 = 0.0;

        double[] tab = new double[4];
        Double[] tab2 = new Double[4];
        System.out.print("[");
        for (double elem : tab)
            System.out.print(elem + " ");
        System.out.println("]");

        System.out.print("[");
        for (Double elem : tab2)
            System.out.print(elem + " ");
        System.out.println("]");

        Scanner scan = new Scanner(System.in);
        String s = scan.nextLine();
        System.out.println(s);
        int n = Integer.parseInt(s);

        Random rand = new Random();

        for (int i=0; i<n; i++) {
            x += rand.nextInt(1,100);
            System.out.println(x);
        }

    }
}