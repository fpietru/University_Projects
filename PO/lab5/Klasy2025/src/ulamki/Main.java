package ulamki;

public class Main {

    public static void main(String[] args) {
        Ulamek u = new Ulamek(1, 4);
        System.out.println(u);

        Ulamek u2 = new Ulamek(1, 16);
        System.out.println(u.equals(u2));

        System.out.println(u.jestMniejszyOd(u2));

        Ulamek u3 = new Ulamek(1, 5);
        Ulamek u4= new Ulamek(2, 3);
        System.out.println(u3.razy(u4));
        System.out.println(u3.podzielPrzez(u4));
        System.out.println(u3.dodaj(u4));
        System.out.println(u3.odejmij(u4));
    }

}
