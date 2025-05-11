#include <stdio.h>

// To jest deklaracja testowanej funkcji.
void transform(char const *s);

int main() {
  transform("a");
  putchar('\n');
  transform("");
  putchar('\n');
  transform("+ab");
  putchar('\n');
  transform("+++abc+de");
  putchar('\n');
  transform("+");
  putchar('\n');
  transform("+x+y");
  putchar('\n');
  transform("+st-abc");
  putchar('\n');
}
