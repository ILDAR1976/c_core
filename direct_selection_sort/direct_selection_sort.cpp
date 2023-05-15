#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void sort(double*, int);
void swap(double*, double*);
double* fill(int);
void print(double*, int);

int main()
{
    int n = 10;
    double* a = fill(n);
    print(a, n);
    sort(a, n);
    print(a, n);
    delete[] a;
    return 0;
}

// invariant: a[0] <= a[1] <= ... <= a[i-1]
//            forall j>i a[j] >= a[i-1]
void sort(double* a, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int m = i; // index of minimal element
        for (int j = i+1; j < n; ++j){
            if (a[j] < a[m]) {
                m = j;
            }
        }
        if (m != i) swap(&a[i], &a[m]);
    }
}
// t ~ n(n-1)/2

void swap(double* x, double* y) {
    double tmp = *x;
    *x = *y; *y = tmp;
}

double* fill(int n) {
    double* a{ new double[n] };
    for (int i = 0; i < n; ++i) a[i] = (double)(rand() % 100);
    return a;
}

void print(double* a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%6.1lf ", a[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
}
