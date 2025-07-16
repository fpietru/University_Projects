#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MXN 1000006

int A[MXN], T[MXN];

void merge(int st, int md, int ed) {
	int i = st;
	int j = md+1;
	int k = st;
	while (i <= md && j <= ed) {
		if (A[i] <= A[j]) T[k++] = A[i++];
		else T[k++] = A[j++];
	}
	while (i <= md) T[k++] = A[i++];
	while (j <= ed) T[k++] = A[j++];
	for (int p=st; p<=ed; p++)
		A[p] = T[p];
}

void mergesort(int st, int ed) {
	if (st == ed) return;
	int md = (st + ed) / 2;
	mergesort(st, md);
	mergesort(md+1, ed);
	merge(st, md, ed);
}

int main () {

	int n = 10;
	for (int i=1; i<=n; i++) {
		A[i] = (rand() % 20) + 1;
		printf("%d ", A[i]);
	}
	printf("\n");
	mergesort(1, n);
	for (int i=1; i<=n; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");

	return 0;
}
