#include <stdio.h>
#include <limits.h>

int sd_max(int tab[], int n) {
	int mx1 = INT_MIN; int mx2 = INT_MIN;
	for (int i=0; i<n; i++) {
		int a = tab[i];
		if (a > mx1) {
			mx2 = mx1;
			mx1 = a;
		}
		else if (a != mx1 && a > mx2)
			mx2 = a;
		// printf("%d %d | %d\n", mx1, mx2, a);
	}
	return mx2;
}

int main() {
	
	int tab[] = {2, 3, 5, 11, -1, 11, 8, 4};		
	int n = sizeof(tab) / sizeof(tab[0]);
	
	printf("%d\n", sd_max(tab, n));
	
	return 0;
}
