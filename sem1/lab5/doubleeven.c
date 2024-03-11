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

void szachownica(int n) {
	int c1 = 3;
	for (int i=0; i<n; i++) {
		int c2;
		if (c1 >= 2) c2 = 1;
		else c2 = 3;
		c1++; c1 %= 4;
		for (int j=0; j<n; j++) {
			if (c2 >= 2)
				kwadrat[i][j] = 0;
			else kwadrat[i][j] = 1;
			c2++; c2 %= 4;
		}
	}
}

void wypelnij(int n) {
	int x = 1;
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++) {
			if (kwadrat[i][j] == 1)
				kwadrat[i][j] = x;
			x++;
		}
	x = 1;
	for (int i=n-1; i>=0; i--)
		for (int j=n-1; j>=0; j--) {
			if (kwadrat[i][j] == 0)
				kwadrat[i][j] = x;
			x++;
		}
}

int main() {
	int n = 0;
	do {
		printf("Podaj rzad kwadratu: ");
		scanf("%d", &n);
		if (n % 4 != 0)
			printf("ma być wielokrotnoscia 4!\n");
	} while (n % 4 != 0);
	szachownica(n);
	wypelnij(n);
	printf("Wynik:\n");
	wypisz(n);
}
