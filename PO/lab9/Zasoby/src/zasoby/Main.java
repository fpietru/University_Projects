package zasoby;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        File f = new File("input/przyklad.txt");
        // try with resources
        try (Scanner scanner = new Scanner(f)) {
            int znaki = 0;
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                System.out.println(line);
                znaki += line.length();
            }
            System.out.println("Laczna dlugosc pliku to " + znaki + " znaki.");
        } catch (FileNotFoundException e) {
            System.err.println("Nie ma takiego pliku na dysku.");
            e.printStackTrace();
        }
    }
}