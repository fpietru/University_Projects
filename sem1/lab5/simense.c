#include <stdio.h>
#include <stdlib.h>
#define ZAKRES 3000

int kwadrat[ZAKRES][ZAKRES];

void wypisz(int n) {
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++)
			printf("%d ", kwadrat[i][j]);
		printf("\n");
	}
}

void wypelnij(int r, int k, int n, int x) {
	if (x > n*n) return;
	kwadrat[r][k] = x;
	if (x%n == 0)
		wypelnij(r+1, k, n, x+1);
	else {
		int r2 = r-1;
		int k2 = k+1;
		if (r2 < 0) r2 = n-1;
		if (k2 >= n) k2 = 0;
		wypelnij(r2, k2, n, x+1);
	}	
}

int main() {
	int n = 0;
	do {
		printf("Podaj rzad kwadratu: ");
		scanf("%d", &n);
		if (n % 2 == 0)
			printf("ma być nieparzysty!\n");
	} while (n % 2 == 0);
	wypelnij(0, n/2, n, 1);
	printf("Wynik:\n");
	wypisz(n);
}
