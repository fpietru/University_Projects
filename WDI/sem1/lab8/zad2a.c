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
	
	for (int i=0; i<=n; i++)
		if (zlozona[i] == 0) {
			while (n % i == 0) {
				printf("%d ", i);
				n /= i;
			}
		}
	printf("\n");
	
	return 0;
}
