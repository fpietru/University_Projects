#include <stdlib.h>
#include <stdio.h>
#define ll long long

ll ilepunktow(int n) {
	ll res = 0;
	for (int x=-n; x<=n; x++) {
		int add = (n-x)*(x+n) + 1;
		// printf("%d %d\n", x, add); 
		res += add;
	}
	return res;
}

int main () {

	printf("%d\n", ilepunktow(3));	

	return 0;
}
