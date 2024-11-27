#include <bits/stdc++.h>
using namespace std;

int max(int t[], int n) {
    int res = t[0];
    for (int i=1; i<n; i++)
        res = max(res, t[i]);
    return res;
}

int main () {
    int n = 6;
    int t[] = {1, 4, 5, 2, 9, 3};
    cout << max(t, n) << "\n";

    return 0;
}