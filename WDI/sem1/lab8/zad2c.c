#include <stdio.h>
#include <stdlib.h>
#define MxN 1000006

int dzielniki[MxN];

int cmp(const void *a, const void *b) {
	int *x = (int *)a;
	int *y = (int *)b;
	return *x - *y;
}

int main () {
	int n;
	scanf("%d", &n);
	
	int ile = 0;
	for (int i=1; i*i<=n; i++)
		if (n % i == 0) {
			int d1 = i;
			int d2 = n / i;
			if (d1 == d2) {
				dzielniki[ile] = d1;
				ile++;
			}
			else {
				dzielniki[ile++] = d1;
				dzielniki[ile++] = d2;
			}
		}
	qsort(dzielniki, ile, sizeof(int), cmp);
	
	printf("Liczba dzielnikow: %d\n", ile);
	printf("Dzielniki: ");
	for (int i=0; i<ile; i++)
		printf("%d ", dzielniki[i]);
	printf("\n");
		
	return 0;
}
