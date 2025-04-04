package bufory;

public class Bufor {
    private String[] tab;
    private int pocz;
    private int kon;
    private int ileElem;

    public Bufor() {
        this(4);
    }

    public Bufor(int poczWielkosc) {
        tab = new String[poczWielkosc];
        pocz = tab.length - 1;
        kon = 0;
    }

    private void rozszerz() {
        if (ileElem == tab.length) {
            String[] tmp = new String[2*tab.length];
            for (int i=0; i< tab.length; i++) {
                tmp[i] = tab[(pocz+1+i) % tab.length];
            }
            pocz = tmp.length - 1;
            kon = tab.length;
            tab = tmp;
        }
    }

    public void pushFront(String elem) {
        ileElem++;
        rozszerz();
        tab[pocz] = elem;
        pocz = (tab.length + pocz - 1) % tab.length;
    }

    public void pushBack(String elem) {
        ileElem++;
        rozszerz();
        tab[kon] = elem;
        kon = (kon + 1) % tab.length;
    }

    public String popFront() {
        pocz = (pocz + 1) % tab.length;
        String res = tab[pocz];
        tab[pocz] = null;
        ileElem--;
        return res;
    }

    public String popBack() {
        kon = (tab.length + kon - 1) % tab.length;
        String res = tab[kon];
        tab[kon] = null;
        ileElem--;
        return res;
    }

    @Override
    public String toString() {
        String res = "[ ";
        for (int i=0; i<tab.length; i++) {
            res += (tab[i] == null ? "_" : tab[i]) + " ";
        }
        res += "] pocz = " + pocz + " kon = " + kon;
        return res;
    }
}
