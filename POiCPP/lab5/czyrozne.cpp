/*
Napisz funkcję bool czyrozne(char* s), która zwraca true
wtw, gdy każde dwa kolejne znaki w napisie s są różne
*/
#include <bits/stdc++.h>
using namespace std;

bool czyrozne(char *s) {
    while ((*s)) {
        if (*(s) == *(s+1))
            return false;
        s++;
    }
    return true;
}

int main () {

    char s[] = "12345";
    cout << czyrozne(s) << "\n";

    return 0;
}