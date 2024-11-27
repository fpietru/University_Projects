#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool pitagoras(int n) {
    for (int a=1; a<=n; a++)
        for (int b=a; b<=n; b++) {
            // cout << a << " " << b << "\n";
            if ((ll)a*a + (ll)b*b == (ll)n*n)
                return true;
        }
    return false;
}

int main () {

    int n; cin >> n;
    cout << pitagoras(n) << "\n";

    return 0;
} 