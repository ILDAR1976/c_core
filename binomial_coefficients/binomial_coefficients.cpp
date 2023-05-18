#include <stdio.h>

void getBinomialCoeff(int*, int);
int* fill(int);
void print(int*, int);


int main()
{
    int n = 30;
    int* a = fill(n+1);
    getBinomialCoeff(a, n);
    print(a,n+1);
    delete[] a;
    return 0;
}

int* fill(int n) {
    int* a{ new int[n] };
    for (int i = 0; i < n; ++i) a[i] = 0;
    return a;
}

void getBinomialCoeff(int* a, int n) {
    a[0] = 1; //C0_0
    for (int k = 1; k <= n; ++k) {
        // calculate coefficients from k per i
        int prev = 0; //preview element
        for (int i = 0; i <= k; ++i) {
           int tmp = a[i];
            if (i < k) {
                a[i] += prev;
                prev = tmp;
            } else {
                a[i] = prev;
            }
        }
    }
}

void print(int* a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

