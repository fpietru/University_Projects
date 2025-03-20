/*
Zadanie domowe 2

Zaimplementuj funkcję rozwiązującą problem wież Hanoi o sygnaturze:
void hanoi(int n, String[] pegs),
gdzie n to ilość dysków, zaś pegs to tablica nazw słupków.
Upewnij się przy użyciu asercji, że liczba dysków jest dodatnia,
że podano nazwy co najmniej trzech słupków i że wszystkie nazwy są różne.
Wszystkie dyski zaczynają na pierwszym słupku, mają się znaleźć na ostatnim,
są numerowane od jedynki, poczynając od najmniejszego.

Np. oczekiwane wyjście dla wywołania hanoi(2, new String[]{"A", "II", "trzy"}) to:
Dysk 1 z A na II
Dysk 2 z A na trzy
Dysk 1 z II na trzy

*/
public class Main {

    public static void moveStack(int stack, int from, int to, int pom, String[] pegs) {
        if (stack == 1) {
            System.out.println("Dysk " + stack + " z " + pegs[from] + " to " + pegs[to]);
        } else {
            moveStack(stack-1, from, pom, to, pegs);
            System.out.println("Dysk " + stack + " z " + pegs[from] + " to " + pegs[to]);
            moveStack(stack-1, pom, to, from, pegs);
        }
    }

    public static void hanoi(int n, String[] pegs) {
        assert(n > 0) : "n has to be positive";
        assert(pegs.length >= 3) : "there should be at least 3 pegs";
        int m = pegs.length;
        for (int i=0; i<m-1; i++)
            for (int j=i+1; j<m; j++)
                assert(!pegs[i].equals(pegs[j])) : "pegs names have to be unique";
        moveStack(n, 0, m-1, 1, pegs);
    }

    public static void main(String[] args) {
        int n = 3;
        String[] pegs = new String[]{"A", "II", "III", "four"};
        hanoi(n, pegs);
    }
}