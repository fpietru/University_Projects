#include <stdio.h>

int main () {
	
	int st = 1, ed = 1000;
	// printf("Set range of numbers [a,b]: ");
	// scanf("%d %d", &st, &ed);

	int nr = 1;
	char odp = 'z';
	while (1) {
		int md = (st + ed) >> 1;
		char odp = 'z';
		printf("Guess no. %d: Is it %d? [y=YES], [u=UP], [d=DOWN] ", nr++, md);
		scanf(" %c", &odp);
		// printf("afds");
		if (odp == 'u') st = md;
		else if (odp == 'd') ed = md;
		else break;
	}

	return 0;
}
