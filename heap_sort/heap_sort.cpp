#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void sort(double*, int);
void sieve(double*, int, int);
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

void sort(double* a, int n) {
    //step 1: pyramid building
    int k = n / 2; //k has no children
    while (k > 0) {
        //invariant: |   ...     : |piramyd ...   |
        //                      k
        --k;
        sieve(a,n, k);
    }
    //step 2:sorting by pyramid
    k = n;
    while (k > 1) {
        //invariant: | piramyd  ...     : |sorted...   |
        //                               k
        //elements a[0],...,a[n-1] - pyramyd
        //a[r] <= a[k+1] <= ... <= a[n-1]
        // a[i] <= a[k] at i < k
        --k;
        swap(&(a[0]), &(a[k]));
        sieve(a, k, 0);
    }
}

void sieve(double* a, int n, int i) {
    //i - index of the sieved element
    while (true){
        int s0 = 2 * i + 1;
        if (s0 >= n) break;
        int s1 = s0 + 1;
        int s = s0;
        if (s1 < n && a[s1] > a[s0]) s = s1;
        if (a[i] >= a[s]) break;
        swap(&(a[i]), &(a[s]));
        //Going down the tree
        i = s;
    }

}

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
        printf("%5.1lf ", a[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
}
