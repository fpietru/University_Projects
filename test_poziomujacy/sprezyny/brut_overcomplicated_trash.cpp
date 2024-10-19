#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
#define FR first
#define SD second
#define PB push_back
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__) // debugging /*
template <typename T> struct tag:reference_wrapper <T>{ using reference_wrapper <T>::reference_wrapper; };
template <typename T1, typename T2> static inline tag <ostream> operator<<(tag <ostream> os, pair<T1, T2> const& p){ return os.get()<<"{"<<p.first<<", "<<p.second<<"}", os;}
template <typename Other> static inline tag <ostream> operator<<(tag <ostream> os, Other const& o){ os.get()<<o; return os; }
template <typename T> static inline tag <ostream> operator <<(tag <ostream> os, vector <T> const& v){ os.get()<<"["; for (int i=0; i<v.size(); i++) if (i!=v.size()-1) os.get()<<v[i]<<", "; else os.get()<<v[i]; return os.get()<<"]", os; }
template <typename T> static inline tag <ostream> operator <<(tag <ostream> os, set <T> const& s){ vector <T> v; for (auto i: s) v.push_back(i); os.get()<<"["; for (int i=0; i<v.size(); i++) if (i!=v.size()-1) os.get()<<v[i]<<", "; else os.get()<<v[i]; return os.get()<<"]", os; }
template <typename ...Args> void logger(string vars, Args&&... values) { cout<<"[ "<<vars<<" = "; string delim=""; (..., (cout<<delim<<values, delim=", ")); cout <<" ]\n"; }
/**/


constexpr int MxN = 1e6+6;
constexpr ll MOD = 1e9+7;
int tab[MxN];
ll ans[MxN];
int poziom[MxN];
int query[MxN];
int idx;

ll suma(int st, int ed) {
	return (st + ed)*(ed - st + 1) / 2;
}

ll przejscie(int k) {
	ll koszt = 0LL;
	for (int i=1; i<=k-1; i++) {
		cout << i << " " << tab[i] << " " << poziom[k-1] << " " << poziom[k] << " " << koszt << "\n";
		if (tab[i] <= poziom[k-1]) {
			koszt += suma((poziom[k-1] - tab[i])+1, (poziom[k] - tab[i]));
			cout << "dodaje " << suma((poziom[k-1] - tab[i])+1, (poziom[k] - tab[i])) << "\n";
		}
		else if (poziom[k-1] < tab[i] && tab[i] < poziom[k]) {
			koszt -= suma(1, (tab[i] - poziom[k-1]));
			koszt += suma(1, (poziom[k]-tab[i]));
		}
		else {
			koszt -= suma((tab[i] - poziom[k])+1, (tab[i] - poziom[k-1]));
		}
	}
	if (tab[k] > poziom[k]) {
		cout << "na koniec " << suma(1, (tab[k] - poziom[k])) << "\n";
		koszt += suma(1, (tab[k] - poziom[k]));
	}
	return koszt;
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	for (int i=1; i<=n; i++)
		cin >> tab[i];
	for (int i=1; i<=m; i++)
		cin >> query[i];
	
	sort(tab+1, tab+n+1);
	
	ans[1] = 0;
	poziom[1] = tab[1];
	
	for (int k=2; k<=n; k++) {
		ll mi = MOD+1;
		int best_poziom = -1;
		
		for (int p = 1; p<=tab[k]; p++) {
			poziom[k] = p;
			ll koszt = przejscie(k);
			cout << "tymczasowy poziom " << p << " "  << "koszt: " << koszt << "\n";
			if (mi > koszt) {
				mi = koszt;
				best_poziom = p;
			}
		}
		poziom[k] = best_poziom;
		cout << "dla k= " << k << " poziom= " << poziom[k] << "\n";
		ans[k] = (ans[k-1] + mi) % MOD;
	}
	
	for (int i=1; i<=m; i++)
		cout << ans[query[i]] << "\n";

	return 0;
}
