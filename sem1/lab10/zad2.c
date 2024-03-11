#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* dec2bin(int n) {
	char *ans;
	ans = (char *) malloc(64 * sizeof(char));
	strcpy(ans, "");
	int m = 0;
	while (n) {
		if (n&1) strcat(ans, "1");
		else strcat(ans, "0");
		n >>= 1;
		m++;
	}
	char *ret;
	ret = (char *) malloc(64 * sizeof(char));
	for (int i=m-1; i>=0; i--)
		ret[m-1-i] = ans[i];
	return ret;
}

int bin2dec(char *s) {
	int res = 0;
	int p = 1;
	char s2[64];
	int rozmiar = 0;
	
	while (*s) {
		s2[rozmiar++] = *(s++);
	}
	
	for (int i=rozmiar-1; i>=0; i--) {
		// printf("%c", s2[i]);
		if (s2[i]&1) res += p;
		p *= 2;
	}
	
	return res;
}

char* convert(char *num, int base1, int base2) {
	
}

int main () {
	
	printf("%s\n", dec2bin(10));
	printf("%s\n", dec2bin(9000));

	char liczba[] = "1010";
	printf("%d\n", bin2dec(liczba));

	return 0;
}
