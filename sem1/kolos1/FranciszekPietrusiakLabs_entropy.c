// Autor: Franciszek Pietrusiak
#include <stdio.h>
#include <string.h>
#include <math.h>

#define alph 300

void wypisznaekran() {
	char znak;
	FILE *czyt = fopen("/tmp/entropy.txt", "r");
	while ((znak = getc(czyt)) != EOF)
		printf("%c", znak);	
	fclose(czyt);
}

int main () {
	FILE* fin = fopen("data.txt", "r");
	FILE* fout = fopen("/tmp/entropy.txt", "w");
	
	if (fin == NULL) {
		printf("Blad przy otwieraniu pliku\n");
		return 1;
	}
	
	char znak;
	int suma = 0;
	int zlicz[alph];
	memset(zlicz, 0, sizeof(zlicz));
	
	fprintf(fout, "The file content is:\n");
	while ((znak = getc(fin)) != EOF) {
		fprintf(fout, "%c", znak);
		if (('a' <= znak && znak <= 'z') || ('A' <= znak && znak <= 'Z') || ('0' <= znak && znak <= '9') || znak == ' ') {
			zlicz[znak]++;
			suma++;
		}
	}
	fprintf(fout, "\n");
	
	fprintf(fout, "Alphabet of symbols in the string:\n");
	for (int i=0; i<alph; i++)
		if (zlicz[i] > 0)
			fprintf(fout, "'%c' ", i);
	fprintf(fout, "\n\n");
	
	float entropy = 0.0;
	fprintf(fout, "Frequencies of alphabet symbols:\n");
	for (int i=0; i<alph; i++)
		if (zlicz[i] > 0) {
			float freq = (float)zlicz[i] / (float)suma;
			fprintf(fout, "%.3f -> '%c'\n", freq, i);
			entropy += freq * log2f(freq);
		}
	
	entropy *= -1.0;
	fprintf(fout, "\nThe entropy is: %.05f\n", entropy);
		
		
	fclose(fin);
	fclose(fout);
	wypisznaekran();
	
	return 0;
}
