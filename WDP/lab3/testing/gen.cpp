#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
    return a + rand() % (b-a+1);
}

int main (int argc, char *argv[]) {
    srand(atoi(argv[1]));

    int q = rand(1, 10);
    for (int k=1; k<=2; k++) {
        int a = rand(-50, 50);
        int b = a + q * rand(1, 20);
        cout << a << " " << q << " " << b << "\n";
    }

    return 0;
}