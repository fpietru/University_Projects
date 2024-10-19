#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int LIMIT = 1e6;
constexpr ll MOD = 1e9+7;
int tab[LIMIT+6];
ll ans[LIMIT+6];
int query[LIMIT+6];

ll suma(int st, int ed) {
	return (st + ed)*(ed - st + 1) / 2;
}

ll oblicz_koszt(int k, int poziom) {
	ll koszt = 0LL;
	for (int i=1; i<=k; i++) {
		if (tab[i] <= poziom)
			koszt += suma(1, (poziom - tab[i]));
		else
			koszt += suma(1, (tab[i] - poziom));
	}
	return koszt;
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	for (int i=1; i<=n; i++) {
		cin >> tab[i];
	}
	for (int i=1; i<=m; i++)
		cin >> query[i];
	
	ll suma = 0;
	for (int k=1; k<=n; k++) {
		ans[k] = 1e18+1;
		suma += tab[k];
		ll sr = suma / k;
		for (int poziom=sr; poziom<=sr+1; poziom++) {
			ll koszt = oblicz_koszt(k, poziom);
			ans[k] = min(ans[k], koszt);
		}
		ans[k] %= MOD;
	}
	
	for (int i=1; i<=m; i++)
		cout << ans[query[i]] << "\n";

	return 0;
}
