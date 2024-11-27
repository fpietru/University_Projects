#include <bits/stdc++.h>
using namespace std;

int main () {

    // petla while
    int kwa=1;
    int niep = 3;
    while (kwa <= 100) {
        cout << kwa << "\n";
        kwa += niep;
        niep += 2;
    }

    // petla for
    for (int kwa=1, niep=3; kwa <= 100; kwa += niep, niep += 2) {
        cout << kwa << "\n";
    }

    for (int i=1; i<=10; i++) {
        cout << (i++) << " " << (++i) << "\n";
    }

    return 0;
} 