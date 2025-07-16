#include <stdio.h>
#include <string.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void kopcuj(int tab[], int n, int i) {
	int najw = i;
	int lewy = 2*i+1;
	int prawy = 2*i+2;
	if (lewy < n && tab[lewy] > tab[najw]) najw = lewy;
	if (prawy < n && tab[prawy] > tab[najw]) najw = prawy;
	if (najw != i) {
		swap(&tab[najw], &tab[i]);
		kopcuj(tab, n, najw);
	}
}

void heapsort(int tab[], int n) {
	for (int i=n-1; i>=0; i--)
		kopcuj(tab, n, i);
	for (int i=n-1; i>=0; i--) {
		swap(&tab[0], &tab[i]);
		kopcuj(tab, i, 0);
	}
}

int main () {

	int tab[] = {8, 2, 1, 3, 18, 18, 9, 3, 4, 7};
	int n = sizeof(tab) / sizeof(tab[0]);
	
	heapsort(tab, n);
	
	for (int i=0; i<n; i++)
		printf("%d ", tab[i]);
	printf("\n");

	return 0;
}
