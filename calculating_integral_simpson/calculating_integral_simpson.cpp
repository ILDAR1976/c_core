#include <stdio.h>
#include <math.h>
#include <assert.h>

double f(double);
double integral(double, double);
double indefineteintegral(double);
double trapeziumFormula(double (*)(double), double, double, int);
double simpsonFormula(double (*)(double), double, double, int);

int main()
{
    double a, b;
    int n;
    while (true) {
        printf("Input a, b, n:\n");
        if (scanf_s("%lf%lf%d", &a, &b, &n) < 3) break;
        double integ = integral(a, b);
        double s0 = trapeziumFormula(&f, a, b, n);
        double s1 = simpsonFormula(&f, a, b, n);
        printf("Integral - %.6lf\n", integ);
        printf("Trapezium formula: %.6lf accuracy=%.6lf\n", s0, fabs(s0-integ));
        printf("Simpson formula: %.6lf accuracy=%.6lf\n",s1, fabs(s1 - integ));
    }

    return 0;
}

double trapeziumFormula(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / (double)n;
    double s = ((*f)(a) + (*f)(b)) / 2.;
    double x = a;
    for (int i = 1; i < n; ++i){
        x += h;
        s += (*f)(x);
    }
    s *= h;
    return s;
}

double simpsonFormula(double (*f)(double), double a, double b, int n) {
    if ((n % 2) != 0) ++n;
    int k = n / 2;
    double h2 = (b - a) / (double)k;
    double h = h2 / 2.;
    double s = ((*f)(a) + (*f)(b)) / 2.;
    double x = a + h;

    for (int i = 0; i < k-1; ++i, x += h2){
        s += (*f)(x) * 2.;
        s += (*f)(x + h);
    }
    assert(fabs((x + h) - b) <= 1e-6);
    s += (*f)(x) * 2.;
    s *= h2 / 3;
    return s;
}

double f(double x) {
    return sin(x);
    // return x*x;
}

double indefineteintegral(double x) {
    return (-cos(x));
    // return x * x * x / 3.;
}

double integral(double a, double b) {
    return indefineteintegral(b) - indefineteintegral(a);
}