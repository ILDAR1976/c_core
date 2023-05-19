#include <stdio.h>
#include <assert.h>

void normalization(double, int*, int*, double*);
void print(char*, int);

int main()
{
    int s = 0, e = 0;
    double x = 100.0, m = 0.;
    printf("dec: %lf\n", x);
    normalization(x, &s, &e, &m);
    printf("normalized form: %c2^%d*%lf\n", ((s==(-1))?'-':'+'),e,m);
    return 0;
}

void normalization(double x, int* sign, int* exponent, double* mant) {
    int s, e;double m;
    s = 1; e = 0; m = x;
    if (x < 0.) {
        s = (-1); m = (-x);
    }
    while (m >= 2.) {
        m /= 2.; ++e;
        //invariant: x == s*m*2^e
    }
    assert(m < 2.);
    while (m < 1.) {
        m *= 2; --e;
    }
    assert(m < 2. && m >= 1);
    *sign = s; *exponent = e; *mant = m;
}


