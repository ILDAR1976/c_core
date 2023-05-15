#include <stdio.h>
#include <math.h>
#include <assert.h>

double squareRoot(double, double);

int main()
{
	double a, r, eps;
	while (true){
		printf("Enter a, eps:\n");
		if (scanf_s("%lf%lf", &a, &eps) < 2 || a < 0.) break;
		r = squareRoot(a, eps);
		printf("r = %lf\n", r);
		printf("Check: r*r=%lf\n", r * r);
	}
 
	return 0;
}

double squareRoot(double a, double eps) {
	assert(a >= 0.);
	double x = a;
	while (fabs(x * x - a) > eps) {
		x = (x + a / x) / 2.;
	}
	return x;
}