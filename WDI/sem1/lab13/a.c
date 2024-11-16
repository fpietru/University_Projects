/*
	Franciszek Pietrusiak
	458987
	(7) Palindromy
*/
#include <stdio.h>
#include <string.h>

int ispalindrome(const char *word) {
	int n = strlen(word);
	if (!n) return 0;
	for (int i=0; i<n; i++)
		if (word[i] != word[n-i-1]) return 0;
	printf("--> %s\n", word);
	return 1;
}

int main () {
	char file[1000], tmp[1000];
	printf("Insert path to the file: ");
	scanf("%s", &file);
	
	int n = strlen(file);
	if (n <= 4 || (file[n-4] != '.' && file[n-3] != 't' || file[n-2] != 'x' || file[n-1] != 't')) {
		sprintf(tmp, "%s.txt", file);
		strcpy(file, tmp);
	}
	
	// printf("%s\n", file);
	
	FILE *fin = fopen(file, "r");

	if (fin == NULL) {
		printf("[ERROR]: Couldn't open input file.\n");
		return 1;
	}
	printf("Searching for palindromes in file [%s]...\n", file);

	int palindromes = 0;
	char ch, word[1000] = ""; 
	while ((ch = fgetc(fin)) != EOF) {
		if (ch == ' ' || ch == '\n' || ch == '\t') {
			palindromes += ispalindrome(word);
			memset(word, 0, sizeof(word));
		}
		else strncat(word, &ch, 1);
	}
	palindromes += ispalindrome(word);
	
	if (!palindromes)	printf("File contains no palindromes.\n");
	else				printf("No. of palindromes found: %d\n", palindromes);

	fclose(fin);
	return 0;
}
