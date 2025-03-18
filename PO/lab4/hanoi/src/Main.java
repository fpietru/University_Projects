public class Main {

    public static void hanoi(int n, String[] pegs) {
        assert(n > 0) : "n has to be positive";
        assert(pegs.length >= 3) : "there should be at least 3 pegs";
        int m = pegs.length;
        for (int i=0; i<m-1; i++)
            for (int j=i+1; j<m; j++)
                assert(pegs[i] != pegs[j]) : "peg's names have to be unique";


    }

    public static void main(String[] args) {
        // String[] pegs = new String[]{"A", "II", "trzy"};
        int n = 3;
        hanoi(n, new String[]{"A", "II", "trzy"});
    }
}