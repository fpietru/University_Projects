#include <stdio.h>
#include <math.h>
#include <string.h>

int main () {
	FILE *fout = fopen("./wyjscie.txt", "w");

	int MXN = 1000;
	for (int a=1; a<=MXN; a++)
		for (int b=0; b<=MXN; b++)
			for (int c=0; c<=MXN; c++)	
				for (int d=2; d<=3; d++) {
					long long wynik = 1;
					for (int i=1; i<=d; i++)
						wynik *= (a + b + c); 
				
					char swynik[20];
					sprintf(swynik, "%lld", wynik);
					char swejscie[20];
					sprintf(swejscie, "%d%d%d", a, b, c);
					if (strcmp(swynik, swejscie) == 0) {
						printf("(%d+%d+%d)^%d\n = %lld\n\n", a, b, c, d, wynik);
						fprintf(fout, "(%d+%d+%d)^%d\n = %lld\n\n", a, b, c, d, wynik);ge
					}
					// printf("%s %s\n\n", swejscie, swynik);
				}

	fclose(fout);
	return 0;
}
