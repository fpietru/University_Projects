/*
Napisz funkcję int f1(char* s), która zwraca długość
najdłuższego palindromu występującego w napisie s.
Zachęcamy do znalezienia rozwiązania efektywnego.
*/
#include <bits/stdc++.h>
using namespace std;

int dl(char* s) {
    int res = 0;
    while (*(s++)) res++;
    return res;
}

bool czy_palindrom(int n, char* s) {
    for (int i=0; i<n/2; i++)
        if (s[i] != s[n-1-i])
            return false;
    return true;
}

int f1(char* s) {
    int n = dl(s);
    int wyn = 0;
    for (int i=0; i<n; i++) {
        for (int j=i; j<n; j++)
            if (czy_palindrom(j-i+1, s+i))
                wyn = max(wyn, j-i+1);
    }
    return wyn;
}

int main () {

    char s[] = "kajak i ala";
    cout << f1(s) << "\n";

    return 0;
}