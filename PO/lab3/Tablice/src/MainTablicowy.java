import java.util.Arrays;
import java.util.Random;

public class MainTablicowy {

    public static final Random RAND = new Random();

    private static int[] generujLosowa(int n, int a, int b) {
        assert(n >= 0) : "Wielkosc tablicy musi byc nieujemna!";
        int[] res = new int[n];
        for (int i=0; i<n; i++) {
            res[i] = RAND.nextInt(a, b);
        }
        return res;
    }

    private static int[] generujLosowa(int n, int k) {
        return generujLosowa(n, 0, k);
    }

    private static int[] czescWspolna(int[] x, int[] y) {
        int[] res = new int[Math.min(x.length, y.length)];
        int i = 0, j = 0, k = 0;
        while (i < x.length && j < y.length) {
            if (x[i] == y[j]) {
                res[k++] = x[i];
                i++; j++;
            } else if (x[i] > y[j]) j++;
            else i++;
        }
        if (k != res.length) {
            int[] tmp = new int[k];
            for (int l=0; l<k; l++)
                tmp[l] = res[l];
            res = tmp;
        }
        return res;
    }

    public static void przykladCzesciWspolnej() {
        int[] a = generujLosowa(10, 10);
        int[] b = generujLosowa(10, 10);
        Arrays.sort(a);
        Arrays.sort(b);
        System.out.println(Arrays.toString(a));
        System.out.println(Arrays.toString(b));
        int[] c = czescWspolna(a, b);
        System.out.println(Arrays.toString(c));
    }

    private static boolean[][] generujLosoweZnajomosci(int n) {
        assert(n > 0);
        boolean[][] res = new boolean[n][n];
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (i == j) res[i][j] = true;
                else res[i][j] = RAND.nextBoolean();
            }
        }
        return res;
    }

    private static void przykladZnajomosci() {
        boolean[][] zna = generujLosoweZnajomosci(10);

    }

    public static void main(String[] args) {
        przykladCzesciWspolnej();

    }

}
