package totolotek;

import java.util.Random;
import java.util.Set;
import java.util.TreeSet;

public class Zaklad {
    private Set<Integer> liczby;

    // losowy zaklad
    public Zaklad() {
        Random random = new Random();
        liczby = new TreeSet<>();
        while (liczby.size() < 6) {
            int liczba = random.nextInt(1, 50);
            liczby.add(liczba);
        }
    }

    // nielosowy zaklad
    public Zaklad(Set<Integer> liczby) {
        if (liczby.size() != 6 || liczby.stream().anyMatch(l -> l < 1 || l > 49)) {
            throw new IllegalArgumentException("Zaklad zawiera 6 liczb z przedzialu [1, 49]");
        }
        this.liczby = new TreeSet<>(liczby);
    }

    public Set<Integer> dajLiczby() {
        return liczby;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Integer liczba : liczby) {
            sb.append(String.format(" %2d ", liczba));
        }
        return sb.toString();
    }
}
