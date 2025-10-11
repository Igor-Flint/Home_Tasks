#include <stdio.h>

int iterative(int n);
int recursive(int m);

int iterative(int num) {
	if ((num == 0) || (num == 1)) return num;
	int i, pres, prev1, prev2;
	prev1 = 0;
	prev2 = 1;
	for (i = 1; i < num; ++i) {
		pres = prev1 + prev2;
		prev1 = prev2;
		prev2 = pres;
	}
	return pres;
}

int recursive(int num) {
	if ((num == 0) || (num == 1)) return num;
	return recursive(num - 1) + recursive(num - 2);
}

main() {
	int i;
	while (scanf("%d", &i) == 1){
		printf("%d-ое число Фибоначчи (посчитано итеративно): %d\n", i, iterative(i));
		printf("%d-ое число Фибоначчи (посчитано рекурсивно): %d\n", i, recursive(i));
	}
}
