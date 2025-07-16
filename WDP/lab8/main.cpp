/*
    Author: Franciszek Pietrusiak
    Code Reviewer: Agnieszka Moskwa
*/
#include <bits/stdc++.h>
using namespace std;

// custom hashing function for unordered_map
struct hashFunction {
    size_t operator()(const vector<int> &vec) const {
        size_t hash = vec.size();
        for (int elem : vec) {
            hash ^= std::hash<int>{}(elem) + 0x9e3779b97f4a7c15 + (hash << 12) + (hash >> 4);
        }
        return hash;
    }
};

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n; cin >> n;
    vector<int> x(n), y(n);
    for (int i=0; i<n; i++) {
        cin >> x[i] >> y[i];
    }

    // g = gcd(x[0], ..., x[n-1])
    int g = x[0];
    for (int i=1; i<n; i++) {
        g = __gcd(g, x[i]);
    }

    // if there exists y[i] that is not a
    // multiple of g then there is no solution
    for (int i=0; i<n; i++)
        if ((y[i] % g) != 0) {
            cout << "-1\n";
            return 0;
        }

    int ans = -1;
    queue<vector<int>> Q;
    // mp[s] = min. number of steps to get
    // from state (0, 0, ..., 0) to state s
    unordered_map<vector<int>, int, hashFunction> mp;
    vector<int> zeros(n, 0);
    Q.push(zeros);
    mp[zeros] = 0;

    // BFS on states
    while (!Q.empty()) {
        vector<int> s = Q.front();
        int steps = mp[s];
        Q.pop();

        // solution found
        if (s == y) {
            ans = steps;
            break;
        }

        auto try2push = [&](const vector<int> &vec) {
            // if state vec not visited then add it to Q
            if (mp.find(vec) == mp.end()) {
                mp[vec] = steps+1;
                Q.push(vec);
            }
        };

        // 1) fill i-th jar with water 
        for (int i=0; i<n; i++) {
            if (s[i] != x[i]) {
                int tmp = s[i];
                s[i] = x[i];
                try2push(s);
                // reverse changes
                s[i] = tmp;
            }
        }

        // 2) pour out all water from i-th jar
        for (int i=0; i<n; i++) {
            if (s[i] != 0) {
                int tmp = s[i];
                s[i] = 0;
                try2push(s);
                s[i] = tmp;
            }
        }

        // 3) pour water from i-th jar into j-th jar
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (i != j && s[i] > 0) {
                    int tmp1 = s[i];
                    int tmp2 = s[j];
                    int r = x[j] - s[j];
                    if (r >= s[i]) {
                        s[j] += s[i];
                        s[i] = 0;
                    } else {
                        s[i] -= r;
                        s[j] = x[j];
                    }
                    try2push(s);
                    s[i] = tmp1;
                    s[j] = tmp2;
                }
            }
        }
    }

    cout << ans << "\n";

    return 0;
}