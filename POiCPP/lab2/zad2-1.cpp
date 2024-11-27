#include <bits/stdc++.h>
using namespace std;

double potega(double x, int d) {
    double res = 1;
    for (int i=1; i<=d; i++)
        res *= x;
    return res;
}

int main () {
    
    cout << potega(-5, 3) << "\n";

    return 0;
} 