#include <stdio.h>
#include <string.h>

int N = 8;
int sols = 0;

void show(int board[N][N]) {
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			if (board[i][j] == 0) printf(".");
			else printf("Q");
		}
		printf("\n");
	}
	printf("\n");
}

int ok(int board[N][N], int line, int col) {
	for (int i=0; i<N; i++) if (board[line][i]) return 0;
	for (int i=0; i<N; i++) if (board[i][col]) return 0;
	for (int i=1; line-i>=0 && col-i>=0; i++) if (board[line-i][col-i]) return 0;
	for (int i=1; line-i>=0 && col+i<N; i++) if (board[line-i][col+i]) return 0;
	return 1;
}

void backtrack(int board[N][N], int line) {
	show(board);
	if (line == N-1) {
		printf("Solution no. %d\n:", ++sols);
		show(board);
	}
	else {
		for (int col=0; col<N; col++) {
			if (ok(board, line, col)) {
				board[line][col] = 1;
				backtrack(board, line++);
				board[line][col] = 0;
			}
		}
	}
}


int main () {

	int board[N][N];
	memset(board, 0, sizeof(board));
	backtrack(board, 0);

	return 0;
}
