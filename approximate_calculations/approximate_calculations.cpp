#include <stdio.h>
#include <assert.h>
#include <math.h>

static const double EPS = 1e-10;
static const double PI = 3.1415926535897323846264;

double mySin(double);

int main()
{
	int res;
	double x;

	while (true) {
		printf("Input x:\n");
		res = scanf_s("%lf", &x);
		if (res <= 0) break;
		printf("mySin(x) = %lf, sin(x) = %lf\n",mySin(x),sin(x));
	}
    return 0;
}

double mySin(double x) {
	if (fabs(x) > PI) {
		x = fmod(x, 2. * PI);
		if (x > PI)
			x -= 2. * PI;
		else if (x < (-PI))
			x -= 2. * PI;
		assert(fabs(x) <= PI);
	}

    double s = 0.;
	double a = x;
	double n = 1.;
	while (fabs(a) > EPS) {
		s += a;
		a = (-a)*x*x / ((n + 1.) * (n + 2.));
		n += 2.;
	}
	return s;
}