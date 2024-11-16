#include <stdio.h>
#define ld long double

ld f(ld x) {
	return x*x*x - x - 2;
}


int main () {

	ld eps = 1e-2;
	ld st = 1.0, ed = 2.0, md;
	printf("Step\tst\ted\tmd\tf(md)\n");
	int step = 1;
	while (ed - st >= eps) {
		md = (st + ed) / 2;
		printf("%d\t%Lf\t%Lf\t%Lf\t%Lf\n", step++, st, ed, md, f(md));
		if (f(md)*f(st) < 0) ed = md;
		else st = md;
	}
	
	printf("The value of root is: %0.10Lf with %0.10Lf precision\n", md, eps);

	return 0;
}
