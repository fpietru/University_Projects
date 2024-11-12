#include <bits/stdc++.h>
using namespace std;

int RAND(int a, int b) {
    return a + rand() % (b-a+1);
}

int main (int argc, char* argv[]) {
    srand(stoi(argv[1]));

    int n = RAND(1, 100);
    int k = 3;
    cout << n << "\n";
    int odl = RAND(0, 20);

    for (int i=1; i<=n; i++) {
        cout << RAND(1, k) << " " << odl << "\n";
        odl += RAND(0, 20);
    }

    return 0;
}