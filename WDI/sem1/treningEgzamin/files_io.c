#include <stdio.h>
#include <string.h>

void sposob1() { // getc() // znak po znaku
	FILE *fin = fopen("./plik.txt", "r");
	
	char znak;
	while ((znak = getc(fin)) != EOF) {
		printf("%c", znak);
	}

	fclose(fin);
}

void sposob2() { // getline() // wiersz po wierszu
	FILE *fin = fopen("./plik.txt", "r");
	
	char *wiersz = NULL;
	size_t dl = 0;
	while (getline(&wiersz, &dl, fin) != -1) {
		printf("%s", wiersz);
	}
	
	fclose(fin);
}

void sposob3() { // fscanf() // wyraz po wyrazie
	FILE *fin = fopen("./plik.txt", "r");
	
	char wyraz[30];
	while (fscanf(fin, "%s", wyraz) != EOF) {
		printf("%s\n", wyraz);
	}
	
	fclose(fin);
}


int main () {

	sposob1();
	sposob2();
	sposob3();

	return 0;
}
