#include <stdio.h>

#define MX_monety 10
#define MX_kwota 1000000
#define INF 1e9+7

int dp[MX_kwota][MX_monety];
int tb[2][MX_kwota][MX_monety];
int zlicz[MX_monety];

int min(int a, int b) {
	if (a <= b) return a;
	else return b;
}

int main() {
	
	int monety[] = {1, 2, 5, 10, 20, 50, 100, 200, 500};
	int m = sizeof(monety) / sizeof(monety[0]);
	
	int kwota;
	scanf("%d", &kwota);
	
	/*
	dp[k][i] = minimalna liczba monet aby rozmienic kwote k uzywajac pierwszych i monet
	dp[0][0] = 0;
	dp[k>0][0] = INF;
	dp[0][i>0] = INF;
	
	                nie biore       biore i-ta monete
	dp[k][i] = min(dp[k][i-1],      dp[k-moneta[i]][i] + 1);
	*/
	
	dp[0][0] = 0;
	for (int k=1; k<=kwota; k++) dp[k][0] = INF;
	for (int i=1; i<=m; i++) dp[0][i] = 0;
	
	for (int k=1; k<=kwota; k++) {
		for (int i=1; i<=m; i++) {
			dp[k][i] = dp[k][i-1];
			tb[0][k][i] = k;
			tb[1][k][i] = i-1;
			if (k >= monety[i-1]) {
				dp[k][i] = min(dp[k][i], dp[k-monety[i-1]][i]+1);
				if (dp[k][i] == dp[k-monety[i-1]][i]+1) {
					tb[0][k][i] = k - monety[i-1];
					tb[1][k][i] = i;
				}
			}
		}
	}
	
	int k = kwota;
	int n = m;
	
	while (k > 0 && n > 0) {
		if (tb[1][k][n] == n)
			zlicz[n-1]++;
		k = tb[0][k][n];
		n = tb[1][k][n];
	}
	
	// printf("%d \n", dp[kwota][m]);
		
	for (int i=0; i<m; i++) {
		printf("Nominal % 4d: %d szt.\n", monety[i], zlicz[i]);
	}
		
	return 0;
}
