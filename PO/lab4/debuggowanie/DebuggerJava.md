# Debugowanie programów Java

Debugowanie (odpluskwianie) jest jedną z najważniejszych technik znajdowania i naprawiania błędów w programach. Polega ona na nadzorowanym uruchomieniu programu, pozwalającym na śledzenie wykonania kolejnych instrukcji programu i ich wpływu na stan jego danych. Podstawowym narzędziem służącym do debugowania programów napisanych w języku *Java* jest program **jdb** (The Java Debugger). 

## Program odpluskiwający **jdb**

Debuger **jdb** działa w terminalu (konsoli, wierszu poleceń) i do jego uruchomienia wystarczy użyć polecenie 
```
jdb [NazwaGłównejKlasy]
```
z opcjonalną nazwą głównej klasy programu (zawierającej metodę `main`). Komenda ta inicjuje środowisko do nadzorowanego uruchomienia programu Java. W środowisku tym pracujemu za pomocą poleceń, z których najważniejsze prezentuje następująca lista:
* `help` lub `?` - wyświetla listę poleceń debugera **jdb**,
* `run` - uruchamia program (jeśli podczas uruchamiania debugera **jdb** nie podało się nazwy głównej klasy, to trzeba to zrobić w tym poleceniu),
* `version` - wyświetla informację o wersji debuggera,
* `exit` lub `quit` - kończy pracę debuggera,
* `stop at <klasa>:<linia>` - ustawia pułapkę w podanej linii,
* `stop in <klasa>.<metoda>` - ustawia pułapkę na pierwszej instrukcji podanej metody,
* `clear` lub `stop` - podaje listę ustawionych pułapek,
* `clear <klasa>:<linia>` - usuwa pułapkę ustawioną w podanej linii,
* `clear <klasa>.<metoda>` - usuwa pułapkę ustawioną w podanej metodzie,
* `step` - wykonuje bieżącą linię i przechodzi do następnej,
* `step up` - wykonuje kod aż do momentu, gdy bieżąca metoda wróci do miejsca, w którym została wywołana,
* `next` - wykonuje bieżącą linię (bez wchodzenia do wnętrza ewentualnego wywołania),
* `cont` - kontynuuje wykonanie kodu od bieżącego miejsca do napotkania kolejnej pułapki lub do końca programu,
* `list` - wyświetla kod źródłowy w okolicy bieżącego miejsca zatrzymania programu,
* `locals` - wyświetla wszystkie zmienne lokalne dostępne w bieżącej ramce stosu wywołań (wymaga wcześniejszej kompilacji programu z opcją `-g`),
* `classes` - wyświetla listę aktualnie znanych klas,
* `class <klasa>` - wyświetla szczegóły podanej klasy (o ile jest znana w bieżącym momencie),
* `methods <klasa>` - wyświetla listę metod podanej klasy (o ile jest znana),
* `fields <klasa>` - wyświetla listę pól podanej klasy (o ile jest znana),
* `print <wyrażenie>` lub `eval <wyrażenie>` - oblicza i wyświetla wartość podanego wyrażenia,
* `dump <obiekt>` - wyświetla wszystkie dane obiektu,
* `set <element> = <wyrażenie>` - przypisuje nową wartość do podanego elementu (zmiennej, pola),
* `where` - wyświetla aktualny stos wywołań,
* `trace methods` - zatrzymuje wykonanie kodu podczas wchodzenia do i wychodzenia z metod (śledzi metody),
* `untrace` - przestaje śledzić metody,
* `!!` - powtarza ostatnią komendę.

### Ćwiczenie 1 (w terminalu)

1) We wspólnym katalogu utwórzmy następującą klasę `Main.java`
``` java
public class Main {
    public static void main(String[] args) {
      int[] array = new int[10];
      for (int i = 0; i < 10; ++i) {
        array[i] = 7 * i;
      }
      System.out.println(array[9]);

      Point2D p = new Point2D(1.0f, -1.0f);
      System.out.println("(" + p.getX() + ", " s+ p.getY() + ")");
    }
}
```
i klasę `Point2D.java`
``` java
public class Point2D {
    private float x;
    private float y;

    public Point2D(float cx, float cy) {
        x = cx;
        y = cy;
    }

    public float getX() {
        return x;
    }
    
    public float getY() {
        return y;
    }
};
```

2) Skompilujmy program poleceniem `javac -g Main.java`.

3) Zainicjujmy środowisko debuggera **jdb** otwierając je do pracy z główną klasą naszego programu. W tym celu wykonajmy polecenie `jdb Main`.
```
Initializing jdb ...
>
```

4) Ustawmy pułapkę (punkt zatrzymania) na początku naszego programu, za pomocą komendy `stop in Main.main`, a następnie rozpocznijmy proces jego debugowania poleceniem `run`. W rezultacie maszyna wirtualna Javy została uruchomiona, a wykonanie programu zatrzymało się a linii
``` java
3          int[] array = new int[10];
```
bezpośrednio przed jej wykonaniem. Chcąc obejrzeć większy fragment kodu w okolicy punktu zatrzymania wykonajmy komendę `list` (symbol `=>` wskazuje miejsce zatrzymania).
``` java
1    public class Main {
2      public static void main(String[] args) {
3 =>     int[] array = new int[10];
4        for (int i = 0; i < 10; ++i) {
5          array[i] = 7 * i;
6        }
7        System.out.println(array[9]);
8
9        Point2D p = new Point2D(1.0f, -1.0f);
10        System.out.println("(" + p.getX() + ", " + p.getY() + ")");
```

5) Poleceniem `step` lub `next` wykonajmy bieżącą instrukcję. W rezultacie utworzona została tablica `array`. Informację o niej można uzyskać poleceniem `locals`
```
Local variables:
array = instance of int[10]
```
a jej aktualną zawartość można obejrzeć komendą `dump array`
```
array = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0
}
```
Samo wykonanie programu zatrzymało się teraz na następnej linii
``` java
4        for (int i = 0; i < 10; ++i) {
```
(zobaczmy także `list`).

6) Kolejne wykonanie polecenia `step` lub `next` przechodzi do linii
``` java
5          array[i] = 7 * i;
```
Tym razem pojawiła się nowa zmienna lokalna `i` o wartości `0` (zob. `locals` i `dump i`). Wywołajmy `step` lub `next` kolejne 3 razy. Program zatrzymał się ponownie przed wykonaniem linii 
``` java
4        for (int i = 0; i < 10; ++i) {
```
co jest oczywiste, gdyż dotarliśmy do pętli. Tym razem jednak inna jest zawartość tablicy `array` (zob. `dump array`)
```
array = {
0, 7, 0, 0, 0, 0, 0, 0, 0, 0
}
```
oraz wartość zmiennej `i` (zob. `dump i`).
``` java
i = 1
```

7) Załóżmy, że chcemy teraz od razu wykonać kolejne instrukcje, wypełniające pozostałe miejsca w tablicy `array`. W tym celu ustawmy nową pułapkę w linii 7 w pliku `Main.java`, za pomocą polecenia `stop at Main:7`. Zauważmy przy okazji, że polecenie `clear` lub `stop` wyświetla listę aktualnie postawionych pułapek:
```
Breakpoints set:
        breakpoint Main.main
        breakpoint Main:7
```
Możemy teraz uruchomić kod aż do momentu napotkania naszej nowej pułapki. Wystarczy skorzystać z polecenia `cont`. W efekcie kod zatrzymał się na linii
``` java
7        System.out.println(array[9]);
```
zaraz po wyjściu z pętli `for`. Zauważmy, że zmienna `i` przestała być dostępna (zob. `locals`), a zawartość tablicy `array` przyjęła postać
```
array = {
0, 7, 14, 21, 28, 35, 42, 49, 56, 63
}
```
(zob. `dump array`).

8) Czasami na potrzeby odpluskwiania kodu chcemy sztucznie zmienić wartość jakiejś zmiennej lub pola. Załóżmy, że potrzebujemy żeby tablica `array` zawierała na końcu nie liczbę `63`, a `120`. W tym celu wywołajmy komendę `set array[9] = 120`. Teraz `dump array` podaje następującą zmodyfikowaną zawartość tablicy:
```
array = {
0, 7, 14, 21, 28, 35, 42, 49, 56, 120
}
```
a polecenie `step` lub `next` wyświetla
```
> 120
```
i przechodzi do linii
``` java
9        Point2D p = new Point2D(1.0f, -1.0f);
```

9) Zauważmy w tym momencie, że polecenie `classes` wyświetla dość długą
listę dostępnych na tę chwilę klas. Jest wśród nich `Main`, ale nie ma `Point2D`. Potwierdzają to dodatkowo polecenia `class Main` i `class Point2D`. Pierwsze z nich daje podstawowe informacje o klasie `Main`
```
Class: Main
extends: java.lang.Object
```
drugie natomiast wyświetla jedynie komunikat 
```
"Point2D" is not a valid id or class name.
```

10) Kolejną linię (`Main:9`) wykonać teraz można na dwa sposoby. Pierwszy z nich może wykonać wszystkie instrukcje i wywołania w bieżącej linii i zatrzymać się w kolejnej (`Main:10`). Drugi natomiast może wejść do wnętrza wywoływanej metody `Point2D` i zatrzymać się na jej początku. Załóżmy, że chcemy skorzystać z tego drugiego sposobu, bo interesuje nas co dzieje się wewnątrz tej metody. W tym celu wywołajmy polecenie `step` (użycie `next` spowodowałoby wykonanie kodu według pierwszego sposobu).  
Zauważmy, że wykonanie kodu zatrzymało się w pliku `Point2D.java` w linii
``` java
5        public Point2D(float cx, float cy) {
```
Polecenie `where` pozwala obejrzeć aktualny stos wywołań
```
  [1] Point2D.<init> (Point2D.java:5)
  [2] Main.main (Main.java:9)
```
dostarczający informację, gdzie aktualnie w kodzie się znajdujemy (w 5 linii w `Point2D`, do której trafiliśmy z 9 linii w `Main`).

11) Za pomocą polecenia `step` lub `next` przejdźmy do następnej linii
``` java
6            x = cx;
```
Zobaczmy aktualną zawartość pól w klasie `Point2D`. W tym celu użyjmy poleceń `print x` i `print y` dających odpowiednio
```
 x = 0.0
 y = 0.0
```
lub `dump this` wypisującego
```
this = {
        x: 0.0
        y: 0.0
}
```

12) Załóżmy, że w aktualnie wywoływanej metodzie `Point2D` nie ma już istotnych instrukcji do śledzenia. Chcemy zatem od razu wykonać pozostały w niej kod i powrócić do kodu wywołującego. W tym celu użyjmy polecenie `step up`. W rezultacie znów znaleźliśmy się w pliku `Main.java` w linii
``` java
9        Point2D p = new Point2D(1.0f, -1.0f);
```
Tym razem jednak klasa `Point2D` jest już widoczna (zob. `classes` i `class Point2D`). Co więcej, poleceniem `fields Point2D` zobaczyć można listę jej pól  
```
float x
float y
```
a poleceniem `methods Point2D` listę jej metod (także tych pochodzących z dziedziczenia)
```
Point2D <init>(float, float)
Point2D getX()
Point2D getY()
java.lang.Object registerNatives()
java.lang.Object <init>()
java.lang.Object getClass()
java.lang.Object hashCode()
java.lang.Object equals(java.lang.Object)
java.lang.Object clone()
java.lang.Object toString()
java.lang.Object notify()
java.lang.Object notifyAll()
java.lang.Object wait()
java.lang.Object wait(long)
java.lang.Object wait(long, int)
java.lang.Object finalize()
java.lang.Object <clinit>()
```
Wywołajmy polecenie `step` lub `next` w celu ukończenia tworzenia obiektu `p` typu `Point2D`. Od tego momemtu możemy zobaczyć jego zawartość poleceniem `dump p`
```
p = {
        x: 1.0
        y: -1.0
}
```
13) Kolejną instrukcją do wykonania w programie jest obecnie linia
```
10        System.out.println("(" + p.getX() + ", " + p.getY() + ")");
```
w pliku `Main.java`. Zauważmy, że wywołuje ona dwie metody `Point2D.getX()` i `Point2D.getY()`. Chcąc zobaczyć wnętrza wołanych metod moglibyśmy albo skorzystać z wywołań polecenia `step`, ale ustawić pułapki wewnątrz tych metod. Alternatywnie można zażądać śledzenia metod, które zatrzyma wykonanie kodu podczas każdego wejścia i wyjścia z metody. W tym celu wywołajmy polecenie `trace methods`. Mając aktywny mechanizm śledzenia metod, wywołajmy dwa razy polecenie `cont`. Za pierwszym i drugim razem wykonanie kodu zatrzymuje się w pliku `Point2D.java` w linii
```
11        return x;
```
przy czym za pierwszym razem zatrzymanie oznaczone jest jako `Method entered`, a za drugim jako `Method exited`. Czasem jednak nie chcemy dalej śledzić żadnych metod. Tak jest w naszym przypadku, więc wywołajmy w tym celu polecenie `untrace`. Następnie użyjmy dwa razy polecenie `next` w celu powrotu i wykonania linii `Main:10`. W rezultacie pojawił się wydruk
```
> (1.0, -1.0)
```
a kod zatrzymał się w linii `Main:11`.

14) Choć to nie jest w tym momencie potrzebne, ale usuńmy "dla treningu" postawione wcześniej pułapki. W tym celu wykonajmy polecenia `clear Main.main` i `clear Main:7`. W rezultacie komenda `clear` lub `stop` powinna zamiast listy pułapek wyświetlić jedynie komunikat `No breakpoints set.`.

15) Kolejne `next` lub `step` lub `cont` kończy proces debugowania naszego programu i zamyka środowisko **jdb**.  
Warto oczywiście przy okazji zapamiętać, że w każdym momencie możemy przerwać proces debugowania programu i wyjść z **jdb** za pomocą polecenia `quit` lub `exit`.

## Debuger w środowisku graficznym (**IntelliJ IDEA**)

Korzystanie z debugera w graficznym środowisku programistycznym (IDE) jest zazwyczaj łatwiejsze w porównaniu do terminala, ze względu oczywiście na większą interaktywność. Co więcej, niektóre IDE oferują w tym zakresie wiele dodatkowych udogodnień. Jednym z wartych rozważenia w tym zakresie jest środowisko **IntelliJ IDEA** firmy JetBrains. 

### Ćwiczenie 2 (w IntelliJ)

1) Utwórzmy w środowisku **IntelliJ** nowy projekt zawierający klasę `Main` o następującej postaci:
``` java
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
```

2) Ustawmy pułapkę w linii 19 zawierającej `System.out.println(Fibonacci(6));`. Pułapkę stawiamy klikając na marginesie z lewej strony kodu źródłowego, obok numeru linii, w której chcemy zatrzymać program. Pułapka zostanie oznaczona czerwonym punktem.
![Image](https://students.mimuw.edu.pl/~prutka/dbg_scrs/Pulapka1.png "Ustawienie pułapki")

3) Rozpocznijmy debugowanie klikając przycisk z robakiem, leżący u góry z prawej strony obok przycisku "play". Alternatywnie można użyć skrótu `SHIFT + F9`.  
W rezultacie maszyna Javy została uruchomiona, a wykonanie naszego programu zostało zatrzymane przed wykonaniem podświetlonej (na niebiesko) linii. 
![Image](https://students.mimuw.edu.pl/~prutka/dbg_scrs/StartDebug.png "Rozpoczęcie debugowania")
Na dole ekranu pojawiło się okno `Debug`, w którym po prawej stronie prezentowane są zmienne lokalne i parametry występujące w aktualnej metodzie wraz z ich bieżącymi wartościami. Co ciekawe, wartości te można zmieniać klikając w nie prawym przyciskiem myszy i wybierając z menu podręcznego opcję `Set Value`. Ponad tą listą zmiennych znajduje się pole, w którym możemy podać wyrażenie do obliczenia lub śledzenia. Wpisując tu na przykład `Fibonacci(10)` uzyskamy bezpośrednio wynik tego wywołania, czyli `result = 55`. Po prawej zaś stronie pokazywany jest stos wywołań metod wraz z numerami linii, w których się aktualnie znajdujemy. Na górze okna `Debug` znajdują się przyciski ze strzałkami, pozwalającymi sterować wykonaniem programu. Poczynając od lewej są to:
 * `Step Over` (`F8`) - przejście do następnej linii bez wchodzenia do wnętrza wołanych funkcji,
 * `Step Into` (`F7`) - przejście do następnej linii z wejściem do wnętrza wołanych funkcji (pomijając funkcje wbudowane i biblioteczne),
 * `Force Step Into` (`ALT + SHIFT + F7`) - tak samo jak `Step Into`, ale uwzględniając funkcje wbudowane i bilioteczne,
 * `Step out` (`SHIFT + F8`) - wykonanie kodu aż do momentu, gdy bieżąca metoda wróci do miejsca, w którym została wywołana,
 * `Run to cursor` (`ALT + SHIFT + 9`) - wykonanie kodu do miejsca, w którym znajduje się karetka (o ile leży ona w kodzie dalej niż aktualny punkt zatrzymania).  
Dodatkowe opcje sterowania wykonaniem programu dostarczają przyciski leżące pionowo na lewej krawędzi okna `Debug`. Są to w szczególności:
 * `Rerun` (`CTRL + F5`) - rozpoczęcie debugowania programu od początku,
 * `Resume program` (`F9`) - wykonanie programu do następnej pułapki lub do końca programu,
 * `Stop` (`CTRL + F2`) - zakończenie procesu debugowania,
 * `Mute Breakpoints` - tymczasowe wyłączenie działania pułapek.

4) Kliknijmy teraz 5 razy strzałkę `Step Into`. Powinniśmy wejść do wnętrza wywołania `Fibonacci(6)` i zatrzymać się na pierwszej instrukcji wewnątrz pętli `for`.
![Image](https://students.mimuw.edu.pl/~prutka/dbg_scrs/WnetrzeFibonacci1.png "Wnętrze wywołania Fibonacci(6)")
Zauważmy jak w oknie `Debug` zmienił się stos wywołań metod oraz lista zmiennych lokalnych i parametrów aktualnie wywoływanej funkcji. Klikając w poszczególne pozycje stosu wywołań możemy zobaczyć zmienne lokalne i parametry innych wywołań ze stosu. Zauważmy ponadto jak edytor wyświetla na końcach linii, zwierających zmienne mające przypisaną wartość, informacje o tych wartościach.  
Kliknijmy następnych kilka razy `Step Into` lub `Step Over`, aż do wyjścia z pętli `for` i prześledźmy przy tym jak, i w którym momencie, zmieniają się wartości zmiennych `k`, `fibo` oraz `tmp`. 

5) Dodajmy nową pułapkę w 20 linii kodu (przy instrukcji `System.out.println(Fibonacci(48));`). Nastęnie kliknijmy `Resume program` i 5 razy strzałkę `Step Into`, żeby ustawić się w pierwszej instrukcji pętli `for` wewnątrz wywołania `Fibonacci(48)`.  
Załóżmy, że chcemy teraz sprawdzić czy zmienna lokalna `fibo` przekroczy zakres typu `int`. W tym celu, zamiast wielokrotnie klikać `Step Over` i sprawdzać wartość w `fibo`, możemy postawić pułapkę, która zatrzyma się w określonych warunkach. Ustawmy zatem pułapkę w linii, w której znajduje się program, tzn. 
```
9          fibo += tmp;
```
następnie kliknijmy prawym przyciskiem myszy w tę pułapkę i w polu `Condition` okna, które się pojawiło, wpiszmy warunek `fibo > Integer.MAX_VALUE - tmp`. W ten sposób wykonanie programu zatrzyma się na tej pułapce tylko wtedy, gdy warunek ten będzie spełniony.
![Image](https://students.mimuw.edu.pl/~prutka/dbg_scrs/WarunkowaPulapka.png "Pułapka z warunkiem zatrzymania")
Kliknijmy `Done`, a potem `Resume program`. Zatrzymanie nastąpiło w 47 obrocie pętli `for`, w momencie gdy 
```
fibo = 1836311903
tmp = 1134903170
```
![Image](https://students.mimuw.edu.pl/~prutka/dbg_scrs/PozaZakresem.png "Zatrzymanie przed przekroczeniem zakresu typu int")
Kliknijmy teraz `Step Over` lub `Step Into` i zauważmy, że wartość zmiennej `fibo` rzeczywiście przekroczyła zakres typu `int`, co w efekcie zmieniło jej znak (`fibo = -1323752223`). Dokończenie programu za pomocą `Resume Program` wyświetla wartość `512559680` jako wynik wywołania `Fibonacci(48)`. Dzięki naszej analizie wiemy jednak, że z powodu przekroczenia zakresu `int` nie jest to poprawna wartość. 

### Zadanie
Wykonaj procesy debugowania swoich rozwiązań zadań z poprzednich zajęć. Podczas śledzenia wykonania poszczególnych programów staraj się sprawdzać czy kolejne instrukcje wykonują to co powinny i czy w ich rezultacie wartości zmiennych zawsze są prawidłowe. 