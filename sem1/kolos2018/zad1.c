#include <stdio.h>
#include <string.h>

int funkcja(int A, int B) {
	int n = (A >= B ? A : B);
	int zlozona[n+1];
	memset(zlozona, 0, sizeof(zlozona));
	zlozona[0] = zlozona[1] = 1;
	for (int i=2; i*i<=n; i++)
		if (zlozona[i] == 0)
			for (int j=i*i; j<=n; j+=i)
				zlozona[j] = 1;
	int dzielnikiA[n];
	int dzielnikiB[n];
	int ileA = 0;
	int ileB = 0;
	for (int i=1; i<=A; i++)
		if (A % i == 0 && zlozona[i] == 0)
			dzielnikiA[ileA++]=i;
	for (int i=1; i<=B; i++)
		if (B % i == 0 && zlozona[i] == 0)
			dzielnikiB[ileB++]=i;
	
	/*
	printf("Dzielniki %d:\n",A);
	for (int i=0; i<ileA; i++)
		printf("%d ", dzielnikiA[i]);
	printf("\nDzielniki %d:\n",B);
	for (int i=0; i<ileB; i++)
		printf("%d ", dzielniki[i]); */
	
	if (ileA != ileB) return 0;
	for (int i=0; i<ileA; i++)
		if (dzielnikiA[i] != dzielnikiB[i])
			return 0;
	return 1;
}

int main () {

	printf("%d\n", funkcja(2, 64));
	printf("%d\n", funkcja(63, 147));
	printf("%d\n", funkcja(10, 12));
	printf("%d\n", funkcja(18, 27));

	return 0;
}
