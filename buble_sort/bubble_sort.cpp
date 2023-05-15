#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void sort(double*, int);
void sort2(double*, int);
void swap(double*, double*);
double* fill(int);
void print(double*, int);

int main()
{
    int n = 10;
    double* a = fill(n);
    print(a,n);
    sort2(a, n);
    print(a, n);
    delete[] a;
    return 0;
}

void sort(double* a, int n) {
    bool inverse = true;
    while (inverse) {
        inverse = false;
        for (int i = 0; i < n-1; ++i) {
            if (a[i] > a[i + 1]) {
                swap(&a[i], &a[i + 1]);
                inverse = true;
            }
        }
    }
}

void sort2(double* a, int n) {
    bool inverse = true;
    int k = 0;
    while (inverse) {
        inverse = false;
        for (int i = 0; i < n - 1 - k; ++i) {
            if (a[i] > a[i + 1]) {
                swap(&a[i], &a[i + 1]);
                inverse = true;
            }
        }
        ++k;
    }
}

void swap(double* x, double* y) {
    double tmp = *x;
    *x = *y; *y = tmp;
}

double* fill(int n) {
    double *a { new double[n]};
    for (int i = 0; i < n; ++i) a[i] = (double)(rand() % 100);
    return a;
}

void print(double* a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%6.1lf ", a[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
}
