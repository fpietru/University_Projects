/*
	Zadanie: Modyfikowanie napisu
	Autor Rozwiazania: Franciszek Pietrusiak
*/
#include <bits/stdc++.h>
using namespace std;
#define PB push_back

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	vector<char> napis;
	string s; cin >> s;
	for (int i=0; i<s.size(); i++)
		napis.PB(s[i]);
	
	while (true) {
		char op; cin >> op;
		if (op == 'N') {
			break;
		}
		if (op == 'Z') {
			char a, b;
			cin >> a >> b;
			for (int i=0; i<napis.size(); i++)
				if (napis[i] == a)
					napis[i] = b;
		}
		if (op == 'D') {
			char c;
			cin >> c;
			napis.PB(c);
		}
		if (op == 'U') {
			int n; cin >> n;
			for (int i=1; i<=n; i++)
				napis.pop_back();
		}
	}
	
	for (int i=0; i<napis.size(); i++)
		cout << napis[i];
	cout << "\n";
	
	return 0;
}
