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
	FILE *fin = fopen("./tekst.txt", "r");

	if (fin == NULL) {
		printf("[ERROR]: Couldn't open input file.\n");
		return 1;
	}
	printf("Searching for palindromes...\n");

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
