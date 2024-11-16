#include <stdio.h>

#define MxN 1000006
int zlozona[MxN];

int main () {
	FILE *fout = fopen("/tmp/prime_numbers.txt", "w");
	
	int n;
	scanf("%d", &n);
	
	zlozona[0] = zlozona[1] = 1;
	for (int i=2; i<=n; i++) {
		if (zlozona[i] == 0)
			for (int j=i*i; j<=n; j+=i)
				zlozona[j] = 1;
	}
	
	for (int i=0; i<=n; i++)
		if (zlozona[i] == 0) {
			printf("%d\n", i);
			fprintf(fout, "%d\n", i);
		}
	
	fclose(fout);
	return 0;
}
