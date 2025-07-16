#include <stdio.h>
#define MxN 1000
#define max(a,b) (a >= b ? a : b)

int dp[MxN][MxN];

int main () {	
	int A[] = {1, 3, 4, 6, 7, 2, 1, 3, 4, 5};
	int B[] = {5, 2, 1, 3, 6, 3, 2, 1, 1};
	int n = sizeof(A) / sizeof(A[0]);
	int m = sizeof(B) / sizeof(B[0]);
	
	dp[0][0] = 0;
	for (int i=1; i<=n; i++)
		dp[i][0] = 0;
	for (int j=1; j<=m; j++)
		dp[0][j] = 0;
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++) {
			if (A[i-1] == B[j-1])
				dp[i][j] = dp[i-1][j-1] + 1;
			else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
		
	int ans = dp[n][m];
	printf("%d\n", ans);
	int C[ans];
	
	int k = 0;
	while (n > 0 && m > 0) {
		if (dp[n][m] == dp[n-1][m-1] + 1) {
			// printf("%d ", A[n-1]);
			C[ans-(k++)-1] = A[n-1];
			n--, m--;
		}
		else {
			if (dp[n-1][m] >= dp[n][m-1])
				n--;
			else m--;
		}
	}
	
	for (int i=0; i<ans; i++)
		printf("%d ", C[i]);
	printf("\n");

	return 0;
}
