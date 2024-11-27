/*
Napisz funkcję void f2(char* s), która drukuje napis s, ale
jeśli występują w nim ciągi kolejnych powtórzonych znaków,
to drukuje te znaki tylko raz. Np f(”AAAABC”) zwróci ABC.
*/
#include <iostream>

void f2(char* s) {
    char* i = s;
    while (*i) {
        std::cout << *i;
        char* j = i;
        while (*(j+1) && *(j+1) == *i)
            j++;
        i = j+1;
    }
}

int main () {
    char s[] = "AAAAABBBBCCCCDEEEEFGGG";
    f2(s);

    return 0;
}