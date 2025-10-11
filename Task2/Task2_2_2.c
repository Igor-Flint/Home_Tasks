#include <stdio.h>

main() {
	double x, ai, value, proiz;
	scanf("%lf", &x);
	value = 0;
	while (scanf("%lf", &ai) == 1) {
		proiz = value + proiz * x;
		value *= x;
		value += ai;
	}
	printf("Значение многочлена в точки %f: %.5g\n", x, value);
	printf("Значение производной многочлена в точке %f: %.5g\n", x, proiz);
}
