#include <stdio.h>
#include <string.h>

int funkcja(int n) {
	int zlozona[n+1];
	memset(zlozona, 0, sizeof(zlozona));
	zlozona[0] = 1;
	zlozona[1] = 1;
	for (int i=2; i*i<=n; i++)
		if (zlozona[i] == 0)
			for (int j=i*i; j<=n; j+=i)
				zlozona[j] = 1;
	int A = 0;
	int B = 0;
	for (int i=1; i*i<=n; i++)
		if (n%i == 0 && zlozona[i] == 0) {
			B = A;
			A = i;
		}
	return A*B;
}

int main () {

	printf("%d\n", funkcja(2926));

	return 0;
}
