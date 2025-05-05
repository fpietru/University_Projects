package logic;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class WyrazeniaLogiczneTests {

    @Test
    public void shouldStalaPrintT() {
        Stala stala = new Stala(true);

        assertEquals("T", stala.toString());
    }

    @Test
    public void shouldStalaPrintF() {
        Stala stala = new Stala(false);

        assertEquals("F", stala.toString());
    }


    @Test
    public void shouldStalaTrueBeTrueAtTrue() {
        Stala stala = new Stala(true);

        assertEquals(true, stala.wartosc(true));
    }

    @Test
    public void shouldStalaTrueBeTrueAtFalse() {
        Stala stala = new Stala(true);

        assertEquals(true, stala.wartosc(false));
    }

    @Test
    public void shouldStalaFalseBeFalseAtTrue() {
        Stala stala = new Stala(false);

        assertEquals(false, stala.wartosc(true));
    }

    @Test
    public void shouldStalaFalseBeFalseAtFalse() {
        Stala stala = new Stala(false);

        assertEquals(false, stala.wartosc(false));
    }

    @Test
    public void shouldZmiennaBeEqualArg() {
        Zmienna zmienna = new Zmienna();

        assertTrue(zmienna.wartosc(true));
        assertFalse(zmienna.wartosc(false));
    }

    @Test
    public void shouldNegacjaWork() {
        Negacja n = new Negacja(new Zmienna());

        assertFalse(n.wartosc(true));
        assertTrue(n.wartosc(false));
    }

    @Test
    public void shouldNegacjaPrintSymbol() {
        Negacja n = new Negacja(new Zmienna());

        assertEquals("!(x)", n.toString());
    }

    @Test
    public void shouldKoniunkcjaWork() {
        Stala T = new Stala(true);
        Stala F = new Stala(false);
        Koniunkcja k1 = new Koniunkcja(T, T);
        Koniunkcja k2 = new Koniunkcja(T, F);
        Koniunkcja k3 = new Koniunkcja(F, T);
        Koniunkcja k4 = new Koniunkcja(F, F);

        assertTrue(k1.wartosc(true));
        assertTrue(k1.wartosc(false));
        assertFalse(k2.wartosc(true));
        assertFalse(k2.wartosc(false));
        assertFalse(k3.wartosc(true));
        assertFalse(k3.wartosc(false));
        assertFalse(k4.wartosc(true));
        assertFalse(k4.wartosc(false));
    }

    @Test
    public void shouldKoniunkcjaPrintSymbol() {
        Stala T = new Stala(true);
        Stala F = new Stala(false);
        Koniunkcja k = new Koniunkcja(T, F);

        assertEquals("(T)&&(F)", k.toString());
    }


    @Test
    public void shouldAlternatywaWork() {
        Stala T = new Stala(true);
        Stala F = new Stala(false);
        Alternatywa a1 = new Alternatywa(T, T);
        Alternatywa a2 = new Alternatywa(T, F);
        Alternatywa a3 = new Alternatywa(F, T);
        Alternatywa a4 = new Alternatywa(F, F);

        assertTrue(a1.wartosc(true));
        assertTrue(a1.wartosc(false));
        assertTrue(a2.wartosc(true));
        assertTrue(a2.wartosc(false));
        assertTrue(a3.wartosc(true));
        assertTrue(a3.wartosc(false));
        assertFalse(a4.wartosc(true));
        assertFalse(a4.wartosc(false));
    }

    @Test
    public void shouldAlternatywaPrintSymbol() {
        Stala T = new Stala(true);
        Stala F = new Stala(false);
        Alternatywa a = new Alternatywa(T, F);

        assertEquals("(T)||(F)", a.toString());
    }


}
