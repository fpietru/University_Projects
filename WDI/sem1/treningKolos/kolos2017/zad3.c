#include <stdio.h>

void swap(int *a, int *b) {
	int pom = *a;
	*a = *b;
	*b = pom;
}

void kopcuj(int a[], int n, int i) {
	int najwiekszy = i;
	int lewy = 2*i+1;
	int prawy = 2*i+2;
	if (lewy < n && a[lewy] > a[najwiekszy]) najwiekszy = lewy;
	if (prawy < n && a[prawy] > a[najwiekszy]) najwiekszy = prawy;
	if (najwiekszy != i) {
		swap(&a[i], &a[najwiekszy]);
		kopcuj(a, n, najwiekszy);
	}
}

void heapsort(int a[], int n) {
	for (int i=n/2-1; i>=0; i--)
		kopcuj(a, n, i);
	for (int i=n-1; i>=0; i--) {
		swap(&a[0], &a[i]);
		kopcuj(a, i, 0);
	}
}

void wypisz(int a[], int n) {
	for (int i=0; i<n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int main () {

	int a[] = {10, 18, 17, 15, 14, 12, 11, 9, 8, 6, 5, 4};
	int n = sizeof(a) / sizeof(a[0]);
	
	// buduj_kopiec(a, n);
	heapsort(a, n);
	wypisz(a, n);

	return 0;
}
