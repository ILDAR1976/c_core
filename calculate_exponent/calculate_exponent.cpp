#include <stdio.h>
#include <math.h>

static const double E = 2.7182818284590452354;
static const double EPS = 1e-10;
double myExp(double);

int main()
{
    int res;
    double x;

    while (true) {
        printf("Input x:\n");
        res = scanf_s("%lf", &x);
        if (res <= 0) break;
        printf("myExp(x) = %lf, exp(x) = %lf\n", myExp(x), exp(x));
    }
    return 0;
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
    //multiply s by e to the power of k
    if (k > 0) {
        while (k > 0) {
            s *= E;
            --k;
        }
    } else if (k<0) {
        while (k < 0) {
            s /= E;
            ++k;
        }
    }
    return s;
}