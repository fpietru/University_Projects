package daty;

import java.time.LocalDate;

/*
1) wyrazic jako napis dd.mm.yyyy
2) zwracanie dnia, miesiaca, roku
3) porownanie dwóch dat (przed, rowne, po)
4) przesunac o zadana liczbe dni do przodu
5) sprawdzanie czy rok jest przestepny
*/
public class Data {
    private int dzien; // 1..31
    private int miesiac; // 1.12
    private int rok;

    public Data() {
        LocalDate teraz = LocalDate.now();
        dzien = teraz.getDayOfMonth();
        miesiac = teraz.getMonthValue();
        rok = teraz.getYear();
    }

    public Data(int dzien, int miesiac, int rok) {
        this.dzien = dzien;
        this.miesiac = miesiac;
        this.rok = rok;
    }

    public int getDzien() { return dzien; }
    public int getMiesiac() { return miesiac; }
    public int getRok() { return rok; }

    @Override
    public String toString() {
        return dzien + "." + miesiac + "." + rok;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) return false;
        if (obj == this) return true;
        if (!(obj instanceof Data)) return false;
        Data other = (Data)obj;
        return (this.dzien == other.dzien)
                && (this.miesiac == other.miesiac)
                && (this.rok == other.rok);
    }

    public boolean czyJestemPoDacie(Data data) {
        return rok > data.rok
                || (rok == data.rok && miesiac > data.miesiac)
                || (rok == data.rok && miesiac == data.miesiac
                && dzien > data.dzien);
    }

    public static boolean po(Data d1, Data d2) {
        return d1.czyJestemPoDacie(d2);
    }

    public static boolean czyPrzestepny(int rok) {
        return rok % 4 == 0;
    }

    public boolean czyPrzestepny() {
        return Data.czyPrzestepny(this.rok);
    }


}
