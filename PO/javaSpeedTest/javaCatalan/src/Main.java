public class Main {

    private static final long MOD = 998244353;

    private static long catalan(int n) {
        if (n == 0) return 1L;
        long cn = 0L;
        for (int i=1; i<=n; i++) {
            cn = (cn + (catalan(i-1) % MOD) * (catalan(n-i) % MOD)) % MOD;
        }
        return cn;
    }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        long start = System.nanoTime();

        long cn = catalan(n);

        long finish = System.nanoTime();
        long time = finish - start;
        String res = "res = " + cn + "; took " + time / 1000000 + " ms";
        System.out.println(res);
    }
}