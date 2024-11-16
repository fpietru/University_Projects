#include <stdio.h>

#define MxN 1000006
int zlozona[MxN];

int main() {

	int n;
	scanf("%d", &n);
	
	zlozona[0] = zlozona[1] = 1;
	for (int i=2; i*i<=n; i++)
		if (zlozona[i] == 0) {
			for (int j=i*i; j<=n; j+=i)
				zlozona[j] = 1;
		}
	
	int wynik = 1;	
	if (n <= 2) wynik = -1;
	else {
		int ile = 0;
		while (n >= 2 && ile < 2) {
			if (zlozona[n] == 0) {
				ile++;
				wynik *= n;
			}
			n--;
		}
	}
	
	printf("%d\n", wynik);
		
	return 0;
}
