#include <stdio.h>
#include <math.h>
#include <assert.h>

static const double E = 2.7182818284590452354;
static const double EPS = 1e-12;
double myPow(double,double);
double myExp(double);

int main()
{
    int res;
    double x,y;

    while (true) {
        printf("Input x:\n");
        res = scanf_s("%lf", &x);
        if (res <= 0) break;
        printf("Input y:\n");
        res = scanf_s("%lf", &y);
        if (res <= 0) break;
        printf("myPow(x) = %lf, pow(x) = %lf\n", myPow(x,y), pow(x,y));
    }
    return 0;
}

double myPow(double x, double y) {
    assert(x > 0.);
    double z = 0.;
    while (x < 1./E || x > E || fabs(y) > EPS) {
        if (x < 1./E) {
            x *= E;z -= y;
        } else if (x > E) {
            x /= E;z += y;
        } else {
            x *= x; y /= 2.;
        }
    }

    return myExp(z);
}

double myExp(double x) {
    int k = (int)x;
    x -= (double)k;
    double s = 0.;
    double n = 0.;
    double a = 1.;

    while (fabs(a) > EPS) {
        s += a;
        n += 1.;
        a *= x / n;
    }
    if (k > 0) {
        while (k > 0) {
            s *= E;
            --k;
        }
    }
    else if (k < 0) {
        while (k < 0) {
            s /= E;
            ++k;
        }
    }
    return s;
}