#include <stdio.h>

int power(double m, int n);

main() {
	double x, ai, integral, derative, polynomial;
	int n, i;
	scanf("%d", &n);
	scanf("%lf", &x);
	integral = 0;
	derative = 0;
	polynomial = 0;
	for (i = n ; i >= 0; --i) {
		scanf("%lf", &ai);
		polynomial += ai * power(x, i);
		if (i > 0) {
			derative += ai * i * power(x, i - 1);
		}
		integral += ai * power(x, i + 1) / (i + 1);
	}
	printf("Значение многочлена в точки %.5g: %.5g\n", x, polynomial);
	printf("Значение производной от многочлена в точке %.5g: %.5g\n", x, derative);
	printf("Значение определенного интеграла от многочлена от 0 до %.5g: %.5g\n", x, integral);
}

int power(double base, int n) {
	int i;
	double p;
	p = 1.0;
	for (i = 1; i <= n; ++i) p = p * base;
	return p;
}
