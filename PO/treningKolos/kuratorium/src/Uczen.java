public class Uczen {
    private Zyczenie[] zyczenia;
    private Zyczenie spelnione;

    public Uczen(Zyczenie[] zyczenia) {
        this.zyczenia = zyczenia;
        this.spelnione = null;
    }

    public Zyczenie[] getZyczenia() { return zyczenia; }
    public Zyczenie getSpelnione() { return spelnione; }
    public void setSpelnione(Zyczenie zyczenie) { this.spelnione = zyczenie; }
}
