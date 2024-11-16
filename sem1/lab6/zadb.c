#include <stdio.h>
#include <stdlib.h>

// zasyfiłem się, nie działa

int main() {
	FILE *fptr;
	fptr = fopen("./data.txt", "r");
	
	int line_sz = 255;
	char line[line_sz];
	while (getline()) {
		int word = 0;
		int astart = 0;
		for (int i=0; i<line_sz; i++) {
			if (line[i] == '\n') {
				word = 0;
				astart = 0;
				printf("\n");
			}
			else if (line[i] != ' ' && word == 0) {
				word = 1;
				if (line[i] == 'a')
					astart = 1;
				if (astart)
					printf("%c", line[i]);
				else printf(" ");
				
			}
			else printf(" ");
			
			if (word && astart)
				printf("%c", line[i]);
		}
		//printf("%s", line);
	} 
	
	fclose(fptr);
	return 0;
}
