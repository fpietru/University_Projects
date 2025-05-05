import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class FractionTests {

    @Test
    public void shouldConvertFractionToString() {
        // given
        Fraction fraction = new Fraction(2, 5);

        // then
        assertEquals("2/5", fraction.toString());
    }

    @Test
    public void shouldConvertFractionToDouble() {
        // given
        Fraction fraction = new Fraction(2, 5);

        // then
        assertEquals(2.0 / 5, fraction.toDouble());
    }

    @Test
    public void shouldThrowExceptionWhenDenominatorIsZero() {
        // then
        assertThrows(ArithmeticException.class, () -> new Fraction(1, 0));
    }

    @Test
    public void shouldTwoSameFractionsBeEqual() {
        // given
        Fraction fraction1 = new Fraction(2, 5);
        Fraction fraction2 = new Fraction(4, 10);

        // then
        assertEquals(fraction1, fraction2);
    }

    @Test
    public void shouldTwoDifferentFractionsNotBeEqual() {
        // given
        Fraction fraction1 = new Fraction(2, 5);
        Fraction fraction2 = new Fraction(3, 5);

        // then
        assertNotEquals(fraction1, fraction2);
    }

    @Test
    public void shouldNegatingNumeratorAndDenominatorCancelEachOtherOut() {
        // given
        Fraction fraction1 = new Fraction(2, 5);
        Fraction fraction2 = new Fraction(-2, -5);

        // then
        assertEquals(fraction1, fraction2);
    }

    @Test
    public void shouldAddTwoFractions() {
        // given
        Fraction fraction1 = new Fraction(2, 5);
        Fraction fraction2 = new Fraction(3, 5);
        Fraction fraction3 = new Fraction(1, 1);

        // when
        fraction1.add(fraction2);

        // then
        assertEquals(fraction3, fraction1);
    }

    @Test
    public void shouldSubtractTwoFractions() {
        // given
        Fraction fraction1 = new Fraction(2, 5);
        Fraction fraction2 = new Fraction(3, 5);
        Fraction fraction3 = new Fraction(-1, 5);

        // when
        fraction1.subtract(fraction2);

        // then
        assertEquals(fraction3, fraction1);
    }

    @Test
    public void shouldAddFractionToItself() {
        // given
        Fraction fraction1 = new Fraction(2, 5);
        Fraction fraction2 = new Fraction(4, 5);

        // when
        fraction1.add(fraction1);

        // then
        assertEquals(fraction2, fraction1);
    }

    @Test
    public void shouldSubtractFractionFromItself() {
        // given
        Fraction fraction1 = new Fraction(2, 5);
        Fraction fraction2 = new Fraction(0, 1);

        // when
        fraction1.subtract(fraction1);

        // then
        assertEquals(fraction2, fraction1);
    }

    @Test
    public void shouldMultiplyTwoFractions() {
        // given
        Fraction fraction1 = new Fraction(2, 5);
        Fraction fraction2 = new Fraction(3, 5);
        Fraction fraction3 = new Fraction(6, 25);

        // when
        fraction1.multiply(fraction2);

        // then
        assertEquals(fraction3, fraction1);
    }

    @Test
    public void shouldDivideTwoFractions() {
        // given
        Fraction fraction1 = new Fraction(2, 5);
        Fraction fraction2 = new Fraction(3, 5);
        Fraction fraction3 = new Fraction(2, 3);

        // when
        fraction1.divide(fraction2);

        // then
        assertEquals(fraction3, fraction1);
    }

    @Test
    public void shouldThrowExceptionWhenDividingByFractionEqualToZero() {
        // given
        Fraction fraction1 = new Fraction(2, 5);
        Fraction fraction2 = new Fraction(0, 1);

        // then
        assertThrows(ArithmeticException.class, () -> fraction1.divide(fraction2));
    }
}