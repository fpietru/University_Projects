package wyjatki;

public class NiezgodnoscRozmiarow extends IllegalArgumentException {
    public NiezgodnoscRozmiarow(String komunikat) {
        super(komunikat);
    }
}
