#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void sort(double*, int);
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

void sort(double* a, int n) {
    int i, j, step;
    int tmp;
    for (step = n / 2; step > 0; step /= 2)
        for (i = step; i < n; i++)
        {
            tmp = a[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < a[j - step])
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = tmp;
        }
}

double* fill(int n) {
    double* a{ new double[n] };
    for (int i = 0; i < n; ++i) a[i] = (double)(rand() % 100);
    return a;
}

void print(double* a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%5.1lf ", a[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
}
