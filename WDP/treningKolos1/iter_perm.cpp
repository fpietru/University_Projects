#include <bits/stdc++.h>
using namespace std;

vector<int> iter_perm(const vector<int> &p, unsigned int k) {
    int n = (int)p.size();
    vector<int> res(n, -1);
    for (int i=0; i<n; i++) {
        if (res[i] < 0) {
            vector<int> cykl;
            int v = p[i];
            do {
                cykl.push_back(v);
                v = p[v];
            } while (v != p[i]);
            int m = (int)cykl.size();
            for (int j=0; j<m; j++)
                res[cykl[j]] = cykl[(j + k) % m]; 
        }
    }
    return res;
}

int main () {

    vector<int> vec = {3, 4, 2, 5, 1, 0};
    for (auto u : iter_perm(vec, 2)) {
        cout << u << " ";
    }
    cout << "\n";

    return 0;
}