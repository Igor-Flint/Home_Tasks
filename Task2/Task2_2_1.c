#include <stdio.h>

main() {
	double x, ai, value;
	scanf("%lf", &x);
	value = 0;
	while (scanf("%lf", &ai) == 1) {
		value *= x;
		value += ai;
	}
	printf("Значение многочлена в точки %f: %.5g\n", x, value);
}
