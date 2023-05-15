#include <stdio.h>

int main()
{
    double sum = 0.;
    double x;
	while (scanf_s("%lf",&x) == 1) {
		sum += x;
	}
	printf("Sums = %lf\n", sum);
	return 0;
}