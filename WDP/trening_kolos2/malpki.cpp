/*
    Zadanie "Malpki" z X OI, etap III
    Autor: Franciszek Pietrusiak
*/
#include <bits/stdc++.h>
using namespace std;

constexpr int LIMIT_N = 2e5+5;
constexpr int INF = 1e9+7;
int G[LIMIT_N][2];
bool vis[LIMIT_N];
int waga[LIMIT_N][2];

bool dfs(int v, int cel, int moment) {
    vis[v] = true;
    if (v == cel)
        return true;
    bool wynik = false; 
    for (int i=0; i<2; i++) {
        int u = G[v][i];
        if (waga[v][i] > moment && waga[u][(G[u][i] == v ? i : (i+1)%2)] > moment)
            wynik |= dfs(u, cel, moment);
    }
    return wynik;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m; cin >> n >> m;
    for (int i=1; i<=n; i++) {
        cin >> G[i][0] >> G[i][1];
    }
    
    for (int i=1; i<=n; i++)
        waga[i][0] = waga[i][1] = INF;
    
    for (int i=0; i<m; i++) {
        int a, b;
        cin >> a >> b;
        waga[a][b-1] = i;
    }

    for (int i=1; i<=n; i++) {
        int low = 0;
        int high = m;
        while (low < high) {
            int mid = (low + high) / 2;
            memset(vis, 0, sizeof(vis));
            if (dfs(1, i, mid) == true) {
                low = mid + 1;
            } else high = mid;
        }
        if (low == m)
            cout << -1 << "\n";
        else cout << low+1 << "\n";
    }


    return 0;
}   