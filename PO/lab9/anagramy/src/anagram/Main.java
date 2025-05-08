// Author: Franciszek Pietrusiak
package anagram;

import java.io.File;
import java.io.FileFilter;
import java.io.FileNotFoundException;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        final String dirPath = "./input";

        File dir = new File(dirPath);
        FileFilter filter = new FileFilter() {
            @Override
            public boolean accept(File pathname) {
                return pathname.getName().endsWith(".txt");
            }
        };

        File[] files = dir.listFiles(filter);

        Map<String, List<String>> map = new HashMap<>();

        if (files != null) {
            for (File file : files) {
                try (Scanner scanner = new Scanner(file)) {
                    while (scanner.hasNext()) {

                        String rawWord = scanner.next();
                        StringBuilder builder = new StringBuilder();
                        for (int i = 0; i < rawWord.length(); i++) {
                            char c = rawWord.charAt(i);
                            if (Character.isLetter(c) || Character.isDigit(c)) {
                                builder.append(c);
                            }
                        }
                        String word = builder.toString();
                        char[] charArray = word.toLowerCase().toCharArray();
                        Arrays.sort(charArray);
                        String key = new String(charArray);

                        if (!map.containsKey(key)) {
                            map.put(key, new ArrayList<>());
                        }
                        map.get(key).add(word);
                    }

                } catch (FileNotFoundException e) {
                    System.err.println("This file does not exist.");
                }
            }
        }

        for (List<String> anagramGroup : map.values()) {
            System.out.println(anagramGroup);
        }
    }
}
