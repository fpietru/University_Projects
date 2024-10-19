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
ll ps[MxN];
ll ps2[MxN];
int query[MxN];

ll suma(int st, int ed) {
	return (st + ed)*(ed - st + 1) >> 1;
}

ll prefsum(int st, int ed) {
	return (MOD + ps[ed] - ps[st-1]) % MOD;
}

ll prefsum2(int st, int ed) {
	return (MOD + ps2[ed] - ps2[st-1]) % MOD;
}

ll rozciaganie(int st, int ed, int poziom) {
	ll dl = ed - st + 1;
	ll calosc = (suma(1, poziom) * dl) % MOD;
	ll zielone = (MOD + calosc - prefsum(st, ed)) % MOD;
	ll ile = (dl * poziom - prefsum2(st, ed)) % MOD;
	ll zielone_unormowane = (ile * (poziom+1) - zielone) % MOD;
	
	cout << dl << " " << calosc << " " << zielone << " " << prefsum(st, ed) << " " << ile << " " << zielone_unormowane << "\n";
	
	return zielone_unormowane;
}

ll sciskanie(int st, int ed, int poziom) {
	ll dl = ed - st + 1;
	ll zielone = (MOD + prefsum(st, ed) - (suma(1, poziom) * dl) % MOD) % MOD;
	ll ile = (prefsum2(st, ed) - dl * poziom) % MOD; 
	ll zielone_unormowane = (MOD + zielone - (ile * poziom) % MOD) % MOD;
	
	cout << dl << " " << zielone << " " << prefsum(st, ed) << " " << ile << " " << zielone_unormowane << "\n";
	
	return zielone_unormowane;
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	ps[0] = ps2[0] = 0LL;
	for (int i=1; i<=n; i++) {
		cin >> tab[i];
		ps[i] = (ps[i-1] + suma(1, tab[i])) % MOD;
		ps2[i] = (ps2[i-1] + tab[i]) % MOD;
	}
	for (int i=1; i<=m; i++)
		cin >> query[i];
	
	ll suma = 0LL;
	for (int k=1; k<=n; k++) {
		suma += tab[k];
		ll sr = suma / k;
		ans[k] = 1e18+1;
		for (int poziom=sr; poziom<=sr+1; poziom++) {
			if (poziom > tab[k]) continue;
				
			int low = 1;
			int high = k;
			while (low < high) {
				int mid = (low + high) >> 1;
				if (tab[mid] <= poziom)
					low = mid + 1;
				else high = mid;
			}

			ll roz = rozciaganie(1, low-1, poziom);
			ll sci = sciskanie(low, k, poziom);
			cout << "k = " << k << " p = " << poziom << " " << (roz + sci) % MOD << "\n";
			ans[k] = min(ans[k], roz + sci);
		}
		ans[k] %= MOD;
	}
	
	for (int i=1; i<=m; i++)
		cout << ans[query[i]] << "\n";

	return 0;
}
