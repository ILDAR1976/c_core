#include <stdio.h>

double qen(double, int);

int main()
{
    int n;
    double a;
    printf("Enter a,n:\n");
    scanf_s("%lf%d", &a, &n);
    printf("The degree a = %lf",qen(a,n));
    return 0;
}

double qen(double a, int n) {
    int k = n;
    double b = a,  p = 1;
    // invariant: b^k *p = a^n
    while (k > 0){
        if (k & 1 == 0) {
            k /= 2; b *= b;
        } else {
            --k; p *= b;
        }
    }
    return p;
}
