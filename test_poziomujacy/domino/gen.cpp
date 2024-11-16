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


int rand(int a, int b) {
	return a + rand() % (b-a+1);
}

int main (int argc, char *argv[]) {
	srand(atoi(argv[1]));
	
	while (true) {
		int n = rand(1, 1000);
		vector<int> h(n+1), d(n+1);
		
		for (int i=1; i<=n; i++)
			h[i] = rand(1, 2000);
		
		for (int i=1; i<=n-1; i++)
			d[i] = rand(1, 2000);
		
		bool flag = true;
		for (int i=1; i<=n; i++)
			if (h[i] <= d[i])
				flag = false;
		
		if (flag == true) {
			cout << n << "\n";
			for (int i=1; i<=n; i++)
				cout << h[i] << " ";
			cout << "\n";
			for (int i=1; i<=n-1; i++)
				cout << d[i] << " ";
			cout << "\n";
			break;
		}
	}
	
	
	
	return 0;
}
