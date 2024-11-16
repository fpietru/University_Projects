#include <stdio.h>
#include <stdlib.h>

#define MxN 100006
int tab[MxN];
int tab2[MxN];
int tab3[MxN];

int cmp(const void *a, const void *b) {
	int *x = (int *)a;
	int *y = (int *)b;
	return *x - *y;
}

int main () {
	
	int n;
	scanf("%d", &n);
	for (int i=0; i<n; i++) {
		scanf("%d", &tab[i]);
		tab2[i] = tab[i];
	}
	
	qsort(tab2, n, sizeof(int), cmp);
	
	int inc = 1;
	int dec = 1;
	for (int i=0; i<n; i++) {
		if (tab[i] != tab2[i])
			inc = 0;
		if (tab[i] != tab2[(n-1)-i])
			dec = 0;
		// printf("%d ", tab2[i]);
	}
	// printf("\n");
	
	if (inc == 1)
		printf("Tablica posortowana rosnaco\n");
	else if (dec == 1)
		printf("Tablica posortowana malejaco");
	else
		printf("Tablica nie jest uporzadkowana");
	
	return 0;
}
