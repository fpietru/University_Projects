#include <bits/stdc++.h>
using namespace std;

bool rowne(int t1[], int t2[], int n) {
    for (int i=0; i<n; i++) {
        if (t1[i] != t2[i])
            return false;
    }
    return true;
}

int main () {
    int n = 6;
    int t1[] = {1, 4, 5, 2, 9, 3};
    int t2[] = {1, 4, 5, 2, 9, 3};
    cout << rowne(t1, t2, n) << "\n";

    return 0;
}