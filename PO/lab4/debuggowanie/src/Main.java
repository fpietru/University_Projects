public class Main {
    /*
     * Oblicza n-ty wyraz ciągu Fibonacciego (n >= 0)
     */
    public static int Fibonacci(int n) {
        int fibo = 0;
        int tmp = 1;
        for (int k = 1; k <= n; ++k) {
            fibo += tmp;
            tmp = fibo - tmp;
        }
        return fibo;
    }

    /*
     * Główna funkcja programu
     */
    public static void main(String[] args) {
        System.out.println(Fibonacci(6));
        System.out.println(Fibonacci(48));
    }
}