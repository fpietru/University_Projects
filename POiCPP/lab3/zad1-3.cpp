#include <bits/stdc++.h>
using namespace std;

bool niemalejaca(int t[], int n) {
    for (int i=1; i<n; i++)
        if (t[i-1] > t[i])
            return false;
    return true;
}

int main () {
    int n = 6;
    int t[] = {1, 4, 5, 2, 9, 3};
    cout << niemalejaca(t, n) << "\n";

    return 0;
}