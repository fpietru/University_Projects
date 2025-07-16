#include <bits/stdc++.h>
using namespace std;

int RAND(int a, int b) {
    return a + rand() % (b-a+1);
}

int main (int argc, char *argv[]) {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    srand(stoi(argv[1]));

    int n = RAND(1, 20);
    int mx = RAND(1, 100);

    cout << n << "\n";
    for (int i=1; i<=n; i++) {
        int x = RAND(0, mx);
        int y = RAND(0, x);
        cout << x << " " << y << "\n";
    }

    return 0;
}