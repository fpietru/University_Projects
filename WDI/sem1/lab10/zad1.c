#include <stdio.h>

int main () {
	int n; scanf("%d", &n);
	
	for (int i=2; i*i<=n; i++) {
		while (n % i == 0) {
			printf("%d | %d\n", n, i);
			n /= i;
		}
	}
	if (n > 1)
		printf("% 2d | %d\n", n, n);

	return 0;
}
