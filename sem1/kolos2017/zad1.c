#include <stdio.h>
#include <string.h>
#define bool int
#define true 1
#define false 0
#define max(a, b) (a >= b ? a : b)

bool funkcja(int n, int m) {
	int mx = max(n, m);
	bool zlozona[mx+1];
	memset(zlozona, 0, sizeof(zlozona));
	zlozona[0] = zlozona[1] = true;
	for (int i=2; i*i<=mx; i++)
		if (zlozona[i] == false) {
			for (int j=i*i; j<=mx; j+=i)
				zlozona[j] = true;
		}
	int ile = 0;
	printf("%d %d\n", n, m);
	for (int i=1; i<=mx; i++)
		if (zlozona[i] == false && n % i == 0 && m % i == 0) {
			ile++;
			printf("%d\n", i);
		}
		
	return (ile % 2 == 1);
}

int main () {

	printf("%d\n", funkcja(35, 49));
	printf("%d\n", funkcja(48, 60));
	printf("%d\n", funkcja(13, 14));
	printf("%d\n", funkcja(18, 27));

	return 0;
}
