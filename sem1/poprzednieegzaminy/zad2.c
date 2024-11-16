#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int max(int a, int b) {
	return (a >= b ? a : b);
}

int funkcja() {
	FILE* fin = fopen("./plikzad2.txt", "r");
	char *line = NULL;
	size_t len = 0;
	
	int mx = 0;
	while (getline(&line, &len, fin) != -1) {
		// printf("%s", line);
		mx = max(mx, strlen(line)-1); // -1, bo getline bierze '\n'
	}
	fclose(fin);
	return mx;
}

int main () {
	
	printf("%d\n", funkcja());

	return 0;
}
