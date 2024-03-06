#include <stdio.h>
#define max(a, b) (a >= b ? a : b)

int funkcja(int a[], int n) {
	int dlA;
	int A = 0;
	int B;
	for (int i=1; i<n; i++)
		if (a[i-1] >= a[i])
			B = i, dlA = i-1;
	int ans = 0;
	while (A <= dlA && B < n) {
		while (a[A] > a[B]) B++;
		if (a[A] == a[B])
			ans = max(ans, B-A+1);
		A++;
	}
	return ans;
}

int main () {

	int a[] = {1, 8, 15, 17, 19, 21, 28, 29, 110, 4, 5, 8, 9, 10, 11, 14, 15, 28};
	int n = sizeof(a) / sizeof(a[0]);
	
	printf("%d\n", funkcja(a, n));

	return 0;
}
