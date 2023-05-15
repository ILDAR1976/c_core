#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void sort(double*, int);
void partition(double*, int, int*);
void swap(double*, double*);
double* fill(int);
void print(double*, int);

int main()
{
    int n;
    double* a = NULL;
    while (true) {
        printf("n:\n");
        if (scanf_s("%d", &n) < 1 || n <= 0) break;
        a = fill(n);
        print(a, n);
        printf("\n================\n");
        sort(a, n);
        printf("Sorted:\n");
        print(a, n);
        printf("\n================\n");
        delete[] a;
    }
    return 0;
}

void sort(double* a, int n) {
    if (n <= 1) {
        return;
    } else  if (n == 2) {
        if (a[0] > a[1]) {
            swap(&(a[0]), &(a[1]));
        }
        return;
    }
    // |<= <= <= |         | <= <= <= |
    //          beg    k  beg + k 
    //invariant: segment of array a[0],...,a[beg-1] is sorted,
    //and the segment a[beg+k],...,a[n-1] is also sorted
    //for (i= beg,beg+1,...,beg+h-1) a[beg-1) <= a[i] <= a[beg+k] 
    int beg = 0;
    int k = n;
    while (k > 1) {
        //select the median index
        int m = k / 2;
        partition(a + beg, k, &m);
        int left = m;
        int right = k - left - 1;
        if (left <= right) {
            sort(a + beg, left);
            beg += left + 1;
            k -= left + 1;
        } else {
            // right <= left
            sort(a + beg + m + 1, right);
            k -= right + 1;
        }
    }
}

void partition(double* a, int n, int *m) {
    //first move the median to the beginning of the array
    if (*m != 0) {
        swap(&(a[0]), &(a[*m]));
    }
    double x = a[0];
    //invariant: a[0] == 0 this is median
    //a[1],a[2],...,a[i] <= x
    //a[j],a[j+1],...,a[n-1] >= x
    int i = 0; int j = n;
    while ((j-i) > 1){
        bool changed = false;
        if (a[i + 1] <= x) {
            ++i;changed = true;
        }
        if (j - 1 > i && a[j - 1] >= x) {
            --j; changed = true;
        }
        if (!changed) {
            assert(
                (j - i) > 1 &&
                a[i+1] > x &&
                a[j-1] < x
            );
            ++i; --j;
            swap(&(a[i]), &(a[j]));
        }
    }
    if (i > 0) {
        swap(&(a[0]), &(a[i]));
    }
    *m = i;
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