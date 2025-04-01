package bufory;

public class Main {
    public static void main(String[] args) {
        Bufor b = new Bufor();
        b.pushBack("A");
        b.pushBack("B");
        b.pushBack("C");
        b.pushBack("D");
        b.pushBack("E");
        System.out.println(b);
        b.popBack();
        System.out.println(b);
    }
}
