#include <stdio.h>

int main()
{
    double p = 0, a, t;
    printf("Enter the point t:\n");
    scanf_s("%lf", &t);
    printf("Enter the coefficients of polinom by descending:\n");
    while (scanf_s("%lf",&a) == 1) {
        p = p * t + a;
    }
    printf("The value of polinom in point %lf\n",p);
    return 0;
}