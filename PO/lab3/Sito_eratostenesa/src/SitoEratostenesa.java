import java.util.Arrays;

public class SitoEratostenesa {
    public static int[] sito(int n) {
        boolean[] zlozona = new boolean[n+1];
        int ile = 0;
        for (int i=2; i<=n; i++) {
            if (zlozona[i]) continue;
            zlozona[i] = false;
            ile++;
            for (int j=2*i; j<=n; j+=i)
                zlozona[j] = true;
        }
        int[] pierwsze = new int[ile];
        int k = 0;
        for (int i=2; i<=n; i++)
            if (!zlozona[i])
                pierwsze[k++] = i;
        return pierwsze;
    }

    public static void main(String[] args) {
        assert(args.length == 1) : "Niepoprawna liczba argumentow";
        int n = Integer.parseInt(args[0]);
        assert(n > 0) : "n ma byc dodatnie!";
        int[] a = sito(n);
        System.out.println(Arrays.toString(a));
    }
}
