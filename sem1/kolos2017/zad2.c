#include <stdio.h>

int main () {
	
	int tab[] = {2, 0, 1, 2, 1, 2, 1, 0, 0};
	int n = sizeof(tab) / sizeof(tab[0]);
	
	int i=0;
	int j=n-1;
	while (i < j) {
		while (i < n-1 && tab[i] != 2) i++;
		while (j > 0 && tab[j] != 0) j
		if (i < j && tab[i] == 2 && tab[j] == 0)
			tab[i] = 0, tab[j] = 2;
	}
	
	for (int i=0; i<n; i++)
		printf("%d ", tab[i]);
	printf("\n");
	
	return 0;
}
