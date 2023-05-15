#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void sort1(double*, int);
void sort2(double*, int);
void sort3(double*, int);
void merge(const double*, int, const double*, int, double*);
void mergeBlocks(double*, int, int);
void mergeSortRecursively(double*, int, double*, int*);
void copyArray(double*, int, double*);
void reverseArray(double*, int);
int findUpper(const double*, int, double);
int findLower(const double*, int, double);
void swap(double*, double*);
void swapBlocks(double*, int, int);
double* fill(int);
void print(double*, int);

int main()
{
    int s = 0;
    printf("Select the type of sorting by merge: 1 - top - down, 2 - down - top, 3 - in - place:\n");
    scanf_s("%d", &s);
    int n = 10;
    double* a = fill(n);
    print(a, n);
    switch (s)
    {
        case 1: 
            sort1(a, n);
            printf("top-down\n");
            break;
        case 2:
            sort2(a, n);
            printf("down-top\n");
            break;
        case 3:
            sort3(a, n);
            sort2(a, n);
            printf("in-place\n");
            break;
        default:
            break;
    }
    print(a, n);
    delete[] a;
    return 0;
}

void sort1(double* a, int n) {
    // Recursive merge sorting top-down implementation (two-way algorithm).
    // The algorithm is stable, i.e. it keeps the order of equal elements
    if (n <= 1) return;
    double* b { new double[n] };
    int arrayIdx;
    mergeSortRecursively(a, n, b, &arrayIdx);
    if (arrayIdx != 0) copyArray(b, n, a);
    delete[] b;
}

void sort2(double* a, int n) {
    // Merge sorting down-top implementation (two-way algorithm)
    if (n <= 1) return;
    if (n == 2) {
        if (a[0] > a[1]) swap(&(a[0]), &(a[1]));
        return;
    }
    double* b { new double[n] };
    double* src = a;
    double* dst = b;
    int len = 1; // the length of the left sub - array of the pair
    while (len < n) {
        // invariant: src array is divided into 
        // pairs of sub-arrays of length len (the 
        // latter can be less than the length), 
        // each sub-array is already sorted.
        int i = 0; // index of the beginning of a pair of subarrays
        while (i < n - len) {
            int len2 = len; // the length of the right sub-array of the pair
            if (i + len + len2 > n) {
                len2 = n - (i + len);
            }
            merge(src + i, len, src + i + len, len2, dst + i);
            i += len + len2;
        }
        if (i < n) {
            copyArray(src + i, n - i, dst + i);
        }
        len *= 2;
        // swap src and dst
        double* tmp = src;
        src = dst; dst = tmp;
    }
    if (src != a) copyArray(b, n, a);
    delete[] b;
}

void sort3(double* a, int n) {
    // In-Place merge sort
    // t = O ( n * (log n)^2)
    if (n <= 1)
        return;
    if (n == 2) {
        if (a[0] > a[1])
            swap(&(a[0]), &(a[1]));
        return;
    }

    int len = 1;

    while (len < n) {

        /*...
        printf("Pass: len=%d\n", len);
        printArray(a, n);
        ...*/

        int i = 0;
        while (i < n - len) {
            int len2 = len;
            if (i + len + len2 > n)
                len2 = n - (i + len);
            // Merge a pair of sub-arrays
            mergeBlocks(
                a + i, len, len2
            );
            // Go to the next pair
            i += (len + len2);
        }

        //... printArray(a, n);

        len *= 2;
    }
}

void mergeBlocks(double* a, int len0, int len1) {
    // Merging two blocks without using additional memory.
    // Recursive implementaion. ( t = O(n*log n)
    if (len0 <= 0 || len1 <= 0)
        return;
    int n = len0 + len1;

    if (len0 == 1) {

        int k = findUpper(a + 1, len1, a[0]);
        int i = 0;
        while (i < k) {
            assert(a[i] > a[i + 1]);
            swap(&(a[i]), &(a[i + 1]));
            ++i;
        }
        assert(i >= n - 1 || a[i] <= a[i + 1]);
        return;
    }

    if (len1 == 1) {

        int k = findLower(a, len0, a[n - 1]);
        int i = n - 1;
        while (i > k + 1) {
            assert(a[i - 1] > a[i]);
            swap(&(a[i - 1]), &(a[i]));
            --i;
        }
        assert(i <= 0 || a[i - 1] <= a[i]);
        return;
    }


    assert(len0 > 1 && len1 > 1);
    int c0, c1;
    if (len0 >= len1) {
        c0 = len0 / 2;
        c1 = findUpper(
            a + len0, len1, a[c0]
        );
        assert(len0 + c1 >= n || a[len0 + c1] >= a[c0]);

        swapBlocks(
            a + c0, len0 - c0, c1
        );
    }
    else {
        c1 = len1 / 2;
        c0 =
            findLower(a, len0, a[len0 + c1]) + 1;
        assert(c0 >= len0 || a[c0] >= a[len0 + c1]);
        swapBlocks(
            a + c0, len0 - c0, c1
        );
    }


    mergeBlocks(
        a, c0, c1
    );
    mergeBlocks(
        a + c0 + c1, len0 - c0, len1 - c1
    );

}

void mergeSortRecursively(double* a, int n, double* b, int* arrayIdx) {
    *arrayIdx = 0; //answer in array a
    if (n <= 1) return;
    if (n == 2) {
        if (a[0] > a[1]) swap(&(a[0]), &(a[1]));
        return;
    }
    assert( n > 2 );
    int k = n / 2;
    // k is in array middle 
    int res0, res1;
    // apply sorting to the left half
    mergeSortRecursively(a, k, b, &res0);
    // apply sorting to the right half
    mergeSortRecursively(a+k, n-k, b+k, &res1);
    if (res0 != res1) {
        if (res0 == 0) {
            copyArray(b + k, n - k, a + k);
        } else {
            copyArray(a + k, n - k, b + k);
        }
    }
    if (res0 == 0) {
        merge(a, k, a + k, n - k, b);
    } else {
        merge(b, k, b + k, n - k, a);
    }
    *arrayIdx = 1 - res0;
}

void merge(const double* a, int n, const double* b, int m, double* c) {
    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
        if (a[i] <= b[j]) {
            c[k] = a[i]; ++i;
        } else {
            c[k] = b[j]; ++j;
        }
        ++k;
    }
    while (i < n) {
        c[k] = a[i]; ++i; ++k;
    }
    while (j < m) {
        c[k] = b[j]; ++j; ++k;
    }
}

void copyArray(double* a, int n, double* b) {
    for (int i = 0; i < n; ++i) b[i] = a[i];
}

void reverseArray(double* a, int n) {
    int i = 0, j = n-1;
    while (i<j){
        swap(&(a[i]), &(a[j]));
        ++i; --j;
    }
}

void swap(double* x, double* y) {
    double tmp = *x;
    *x = *y; *y = tmp;
}

void swapBlocks(double* a, int len0, int len1) {
    if (len0 <= 0 || len1 <= 0)
        return;
    if (len0 == len1) {
        for (int i = 0; i < len0; ++i)
            swap(&(a[i]), &(a[i + len0]));
        return;
    }
    reverseArray(a, len0);
    reverseArray(a + len0, len1);
    reverseArray(a, len0 + len1);
}

// The input array "a" is sorted.
// Find the element with minimal index i such that
// a[i] >= x
static int findUpper(
    const double* a, int n, double x
) {
    if (n <= 0 || x <= a[0])
        return 0;
    if (x > a[n - 1])
        return n;
    assert(n > 0 && a[0] < x && x <= a[n - 1]);
    int b = 0; int e = n - 1;
    while (e - b > 1) {
        assert(a[b] < x && x <= a[e]);
        int c = (b + e) / 2;
        if (a[c] < x)
            b = c;
        else
            e = c;
    }
    assert(a[e - 1] < x && x <= a[e]);
    return e;
}

// The input array "a" is sorted.
// Find the element with maximal index i such that
// a[i] <= x
int findLower(
    const double* a, int n, double x
) {
    if (n <= 0 || x < a[0])
        return (-1);
    if (a[n - 1] <= x)
        return n - 1;
    assert(n > 0 && a[0] <= x && x < a[n - 1]);
    int b = 0; int e = n - 1;
    while (e - b > 1) {
        assert(a[b] <= x && x < a[e]);
        int c = (b + e) / 2;
        if (a[c] <= x)
            b = c;
        else
            e = c;
    }
    assert(a[b] <= x && x < a[b + 1]);
    return b;
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
