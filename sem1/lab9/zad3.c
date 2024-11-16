#include <stdio.h>
#include <ctype.h>

int funkcja(char litera) {
	FILE* fin = fopen("./dane.txt", "r");		
	char znak;
	int res = 0;
	int slowo = 0;
	while ((znak = getc(fin)) != EOF) {
		if (('a' <= znak && znak <= 'z') || ('A' <= znak && znak <= 'Z') || ('0' <= znak && znak <= '9')) {
			if (slowo == 0) {
				slowo = 1;
				if (znak == litera || znak == toupper(litera))
					res++;
			}
			// printf("*");
		}
		else {
			slowo = 0;
			// printf("%c", znak);
		}
	}
		
		
	fclose(fin);
	return res;
}

int main() {
	
	printf("%d\n", funkcja('j'));
	
	return 0;
}
