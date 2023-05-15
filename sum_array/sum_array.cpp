#include <stdio.h>
#include <cstdlib>

static double x[20];

double sumArray1(double[],int);
double sumArray2(double[],int);
void print(double[],int);


int main()
{
    int n = sizeof(x) / sizeof(x[0]);
    for (int i = 0; i < n; ++i) {
        x[i] = rand();
    }
    
    print(x, n);
    printf("Sum of array elements by first way: %lf\n", sumArray1(x, n));
    printf("Sum of array elements by first way: %lf\n", sumArray2(x, n));
    return 0;
}

double sumArray1(double x[], int n) {
    double s = 0.;
    for (int i = 0; i < n; ++i) {
        s += x[i];
    }
    return s;
}

double sumArray2(double x[], int n) {
    double s = 0.;
    double *p = x;
    double *q = x + n;
    while (p < q) {
        s += *(p++);
    }
    return s;
}

void print(double x[], int n) {
    double *p = x, *q = x + n;
    while (p < q) printf("%lf\n", *(p++));
    printf("\n");
}


