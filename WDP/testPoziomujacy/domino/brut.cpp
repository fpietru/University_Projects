/*
	Zadanie: Domino
	Autor Rozwiazania: Franciszek Pietrusiak
*/
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
int h[MxN];
bool vis[MxN];
ll dist[MxN];

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	for (int i=1; i<=n; i++)
		cin >> h[i];
	
	dist[1] = 0;
	for (int i=2; i<=n; i++) {
		int d; cin >> d;
		dist[i] = dist[i-1] + d;
	}
	
	queue<pii> Q;
	vis[1] = true;
	Q.push(make_pair(1, 0));
	
	while (!Q.empty()) {
		int v = Q.front().FR;
		int cost = Q.front().SD;
		Q.pop();
		if (v == n) {
			cout << n - (cost+1) << "\n";
			return 0;
		}
		for (int j = v+1; j<=n; j++) {
			if (dist[j] >= dist[v] + h[v])
				break;
			if (vis[j] == false) {
				vis[j] = true;
				Q.push(make_pair(j, cost+1));
			}
		}
	}

	return 0;
}
