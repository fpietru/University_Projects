package daty;

public class Main {
    public static void main(String[] args) {
        Data bn = new Data(24,12,2025);
        Data dzis = new Data();
        System.out.println(bn);
        System.out.println(dzis);
        System.out.println(dzis.czyJestemPoDacie(bn));
    }
}
