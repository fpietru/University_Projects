#include <bits/stdc++.h>
using namespace std;

void ciag(int p, int r, int n) {
    for (int i=1; i<=n; i++) {
        cout << p << " ";
        p += r;
    }
    cout << "\n";
}

int main () {
    
    ciag(1, 3, 5);

    return 0;
} 