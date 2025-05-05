public class Fraction {
    private int numerator;
    private int denominator;

    public Fraction(int numerator, int denominator) {
        if (denominator == 0) {
            throw new ArithmeticException("The denominator cannot be equal to 0.");
        }
        this.numerator = numerator;
        this.denominator = denominator;
        normalise();
    }

    public int getNumerator() {
        return numerator;
    }

    public int getDenominator() {
        return denominator;
    }

    public double toDouble() {
        return ((double) numerator) / denominator;
    }

    @Override
    public String toString() {
        return getNumerator() + "/" + getDenominator();
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Fraction other) {
            return numerator == other.numerator && denominator == other.denominator;
        }
        return false;
    }

    public void add(Fraction other) {
        int otherDenominator = other.denominator;
        numerator = numerator * other.denominator + other.numerator * denominator;
        denominator *= otherDenominator;
        normalise();
    }

    public void subtract(Fraction other) {
        int otherDenominator = other.denominator;
        numerator = numerator * other.denominator - other.numerator * denominator;
        denominator *= otherDenominator;
        normalise();
    }

    public void multiply(Fraction other) {
        numerator *= other.numerator;
        denominator *= other.denominator;
        normalise();
    }

    public void divide(Fraction other) {
        if (other.numerator == 0) {
            throw new ArithmeticException("Cannot divide by zero");
        }
        numerator *= other.denominator;
        denominator *= other.numerator;
        normalise();
    }

    private void normalise() {
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }

        int gcd = gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

    private static int gcd(int x, int y) {
        if (x < 0)
            return gcd(-x, y);
        else
            return x == 0 ? y : gcd(y % x, x);
    }
}