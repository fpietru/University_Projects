/*
Napisz funkcję void drukuj gwiazdki(char* s), która
drukuje na ekranie tekst zawarty w napisie s, w którym ciągi
kolejnych spacji są zastąpione przez znak *
*/
#include <bits/stdc++.h>
using namespace std;

void drukuj_gwiazdki(char *s) {
    for (char* it=s; *it != '\0'; it++) {
        if (*it != ' ') cout << *it;
        else cout << '*';
    }
}

int main () {

    char s[] = "12   3 45\n";
    drukuj_gwiazdki(s);

    return 0;
}