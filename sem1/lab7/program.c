// Franciszek Pietrusiak
#include <stdio.h>
#include <string.h>
#define ll long long

// wzór funkcji do Pana Łukasza Kozłowskiego
void printStats(int uid, ll A_count, ll T_count, ll G_count, ll C_count) {
    ll total_count = A_count + T_count + G_count + C_count;
    if (uid > 0) {
    	if (uid == 23) printf("Total statistics for chromosome X\n");
    	if (uid == 23) printf("Total statistics for chromosome Y\n");
    	if (uid == 23) printf("Total statistics for chromosome M\n");
    	else printf("Total statistics for chromosome %d\n", uid);
    }
    else printf("============================\nTotal statistics for all chromosomes\n\n");
    printf("Length: %lld\n", total_count);
    printf("Nucleotide frequencies:\n");
    printf("A: % 10lld % 5.2f%%\n", A_count, ((double)A_count / total_count) * 100);
    printf("T: % 10lld % 5.2f%%\n", T_count, ((double)T_count / total_count) * 100);
    printf("G: % 10lld % 5.2f%%\n", G_count, ((double)G_count / total_count) * 100);
    printf("C: % 10lld % 5.2f%%\n", C_count, ((double)C_count / total_count) * 100);
    printf("GC content:    %.2f%%\n\n", ((	double)(G_count + C_count) / total_count) * 100);
}

int main () {
	FILE* fin = fopen("./chm13v2.0.fa", "r");
	
	ll cnt_a = 0, cnt_t = 0, cnt_g = 0, cnt_c = 0;
	ll chr_a = 0, chr_t = 0, chr_g = 0, chr_c = 0;
	ll cnt_chromosomes = 0;
	
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	
	while ((read = getline(&line, &len, fin)) != -1) {
		if (line[0] == '>') {
			cnt_chromosomes++;
			if (cnt_chromosomes >= 2) {
				printStats(cnt_chromosomes-1, chr_a, chr_t, chr_g, chr_c);
			}
			chr_a = 0, chr_t = 0, chr_g = 0, chr_c = 0;
		}
		else {
			for (int i=0; i<strlen(line); i++) {
				char c = line[i];
				if (c == 'a' || c == 'A') cnt_a++, chr_a++;
				if (c == 't' || c == 'T') cnt_t++, chr_t++;
				if (c == 'g' || c == 'G') cnt_g++, chr_g++;
				if (c == 'c' || c == 'C') cnt_c++, chr_c++;	
			}
		}
	}
	printStats(25, chr_a, chr_t, chr_g, chr_c);
	printStats(-1, cnt_a, cnt_t, cnt_g, cnt_c);	
	
	
	fclose(fin);
	return 0;
}
