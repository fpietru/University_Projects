#include <bits/stdc++.h>

int cykl(const std::vector<int> p) {
    int n = (int)p.size();
    int res = 0;
    for (int i=0; i<n; i++) {
        int dl = 0;
        int pocz = p[i];
        do {
            dl++;
            pocz = p[pocz];
        } while (pocz != p[i]);
        res = std::max(res, dl);
    }
    return res;
}

int main () {
    std::vector<int> p = {2, 1, 0, 5, 6, 4, 3, 8, 7};
    std::cout << cykl(p) << "\n";

    return 0;
}