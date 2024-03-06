#include <stdio.h>

void funkcja(int A[], int n) {
	int posmi = 0;
	int posmx = 0;
	for (int i=0; i<n; i++) {
		if (A[i] < A[posmi]) posmi = i;
		if (A[i] > A[posmx]) posmx = i;
	}
	int pom = A[posmi];
	A[posmi] = A[0];
	A[0] = pom;
	pom = A[posmx];
	A[posmx] = A[n-1];
	A[n-1] = pom;
}

int main () {

	int A[] = {12, -7, 18, 2, -2, -11, 7};
	int n = sizeof(A) / sizeof(A[0]);
	funkcja(A, n);
	
	for (int i=0; i<n; i++)
		printf("%d ", A[i]);
	printf("\n");

	return 0;
}
