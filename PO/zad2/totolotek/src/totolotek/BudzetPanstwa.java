package totolotek;

public class BudzetPanstwa {
    private long podatki;
    private long subwencje;

    public BudzetPanstwa() {
        this.podatki = 0;
        this.subwencje = 0;
    }

    public long dajPodatki() {
        return podatki;
    }

    public void zbierzPodatek(long kwota) {
        podatki += kwota;
    }

    public long dajSubwencje() {
        return subwencje;
    }

    public long przekazSubwencje(long kwota) {
        subwencje += kwota;
        return kwota;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Budzet Panstwa:\n");
        sb.append(" - Pobrane Podatki: ");
        sb.append(podatki / 100L);
        sb.append(" zl ");
        sb.append(podatki % 100L);
        sb.append(" gr\n");
        sb.append(" - Przekazane Subwencje: ");
        sb.append(subwencje / 100L);
        sb.append(" zl ");
        sb.append(subwencje % 100L);
        sb.append(" gr");
        return sb.toString();
    }
}
