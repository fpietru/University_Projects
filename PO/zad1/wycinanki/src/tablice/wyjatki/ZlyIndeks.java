package tablice.wyjatki;

public class ZlyIndeks extends IllegalArgumentException {
    public ZlyIndeks(String komunikat) {
        super(komunikat);
    }
}
