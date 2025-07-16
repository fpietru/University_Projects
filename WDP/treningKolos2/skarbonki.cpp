/*
    Zadanie "Skarbonki" z XII OI, etap I
    Autor: Franciszek Pietrusiak
*/
#include <bits/stdc++.h>
using namespace std;

constexpr int LIMIT = 1e6+6;
vector<int> G[LIMIT];
bool vis[LIMIT];

void dfs(int v) {
    vis[v] = true;
    for (auto u : G[v]) {
        if (vis[u] == false) {
            dfs(u);
        }
    }
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n; cin >> n;
    for (int i=1; i<=n; i++) {
        int x; cin >> x;
        G[i].push_back(x);
        G[x].push_back(i);
    }

    int ans = 0;
    for (int i=1; i<=n; i++) {
        if (vis[i] == false) {
            dfs(i);
            ans++;
        }
    }

    cout << ans << "\n";

    return 0;
}