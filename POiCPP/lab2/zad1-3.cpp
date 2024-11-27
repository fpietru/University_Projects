#include <bits/stdc++.h>
using namespace std;

int main () {
    
    int x, suma = 0;
    while (true) {
        cin >> x;
        if (x == 0)
            break;
        suma += x;
    }
    cout << suma << "\n";

    return 0;
} 