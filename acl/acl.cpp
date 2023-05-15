#include <stdio.h>
#include <math.h>
#include <assert.h>

double acl(double, double, double);

int main()
{
    double x, y, a, eps;
    while (true){
        printf("Enter y,a,eps:\n");
        if (scanf_s("%lf%lf%lf", &y, &a, &eps) < 3 || a < 0.) break;
        x = acl(y, a, eps);
        printf("log_a(y) = %lf\n", x);
        printf("Check: a^x = %lf\n", pow(a, x));
    }
    return 0;
}

double acl(double y, double a, double eps) {
    assert(a > 0. && a != 1.);
    bool inverse = false;
    if (a < 1.) {
        inverse = true;
        a = 1. / a;
    }
    double x = 0., z = y, t = 1;
    // Invariant: a^x * z^t == y
    while (z < 1./a || z > a || fabs(t) > eps) {
        if (z < 1. / a) {
            z *= a; x -= t;
        } if (z > a) {
            z /= a; x += t;
        } else {
            t /= 2.; z *= z;
        }
    }
    if (inverse) x = (-x);
    return x;
}