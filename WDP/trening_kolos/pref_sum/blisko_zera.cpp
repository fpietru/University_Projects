#include <bits/stdc++.h>

int blisko_zera(std::vector<int> v) {
    int L = -1;
    int P = (int)v.size() - 1;
    while (L + 1 < P) {
        int M = (L+P) / 2;
        if (abs(v[M]) < abs(v[M+1]))
            P = M;
        else L = M;
    }
    return abs(v[P]);
}

int main () {

    std::vector<int> v = {10, 8, 7, -4, -8, -10, -12, -17, -19, -20, -30};
    std::cout << blisko_zera(v) << "\n";

    return 0;
}