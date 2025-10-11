#include <stdio.h>
#define UNIT 1
main() {
	double eps, xi, x, prevX, dif;
	scanf("%lf", &eps);
	dif = 10000;
	while (scanf("%lf", &x) == 1) {
		prevX = UNIT;
		while (dif >= eps) {
			xi = 0.5 * (prevX + (x / prevX));
			if (prevX >= xi) dif = prevX - xi;
			else dif = xi - prevX;
			prevX = xi;
		}
		printf("%.10g\n", xi);
		dif = 10000;
	}
}
