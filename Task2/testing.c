#include <stdio.h>

main()
{
	double x;
	scanf("%lf", &x);
	scanf("%lf", &x);
	if (x == EOF) printf("YES");
	else printf("NO, %.10g", x);
}
