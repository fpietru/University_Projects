/*
	Zadanie: Domino
	Autor Rozwiazania: Franciszek Pietrusiak
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int LIMIT = 1e6;
int wys[LIMIT+11];
ll poz[LIMIT+22];

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	for (int i=1; i<=n; i++)
		cin >> wys[i];
	
	for (int i=2; i<=n; i++) {
		ll x; cin >> x;
		poz[i] = poz[i-1] + x;
	}
	
	if (n <= 2) {
		cout << "0\n";
		return 0;
	}
	
	int biore = 2;
	ll R = wys[1];
	ll nextR = 0;
	
	for (int i=1; i<=n-1; i++) {
		if (R > poz[i]) {
			nextR = max(nextR, poz[i] + wys[i]);
		}
		if (R <= poz[i+1]) {
			R = nextR;
			biore++;
		}
	}
	cout << n - biore << "\n";
	
	return 0;
}
