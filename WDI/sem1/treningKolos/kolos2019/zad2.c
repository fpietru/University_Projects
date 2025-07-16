#include <stdio.h>

int funkcja(int a[], int n, int k) {
	int ile = 1;
	for (int i=1; i<n; i++) {
		if (a[i] > a[i-1]) {
			ile++;
			if (ile == k)
				return 1;
		}
		else ile = 1;
	}
	return 0;
}

int main () {

	int a[] = {12, 9, 7, 8, 23, 7};
	int b[] = {12, 9, 7, 8, 23, 241, 7};
	int c[] = {12, 9, 7, 8, 8, 23, 241, 7};
	int d[] = {12, 13, 14, 8, 5, 6, 7, 7};
	int s1 = sizeof(a) / sizeof(a[0]);
	int s2 = sizeof(b) / sizeof(b[0]);
	int s3 = sizeof(c) / sizeof(c[0]);
	int s4 = sizeof(d) / sizeof(d[0]);
	printf("%d %d %d %d\n", funkcja(a, s1, 3), funkcja(b, s2, 3), funkcja(c, s3, 4), funkcja(d, s4, 4));

	return 0;
}
