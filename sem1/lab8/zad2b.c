#include <stdio.h>
#include <stdlib.h>

#define MxN 1000006
int zlozona[MxN];

int main () {
	int n;
	scanf("%d", &n);
	
	zlozona[0] = zlozona[1] = 1;
	for (int i=2; i<=n; i++) {
		if (zlozona[i] == 0)
			for (int j=i*i; j<=n; j+=i)
				zlozona[j] = 1;
	}
	
	int ile = 0;
	printf("Rozne dzielniki pierwsze liczby %d: ", n);
	for (int i=0; i<=n; i++)
		if (zlozona[i] == 0) {
			if (n % i == 0) {
				printf("%d ", i);
				ile++;
			}
		}
	printf("\n");
	printf("Liczba roznych dzielnikow pierwszych liczby %d to: %d\n", n, ile);
	
	return 0;
}
