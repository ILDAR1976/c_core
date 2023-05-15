#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

bool binSearch(const float*, int, float, int*);
void print(float*,int);


int main()
{
    int n = 1e2;
    float  *a {new float[n] };
    float tmp = 1;a[0] = 0;
    for (int i = 0; i < n; ++i) {
        while (a[i] < tmp) 
            a[i] = ((float)rand()) /1.46;
        tmp = a[i];
    }
    float x;
    int idx = 0;
    print(a,10);
    printf("Enter search number:\n");
    scanf_s("%f", &x);
    if (binSearch(a, n, x, &idx)) 
        printf("The number is %f founded on index %d",x, idx);
    else 
        printf("The number is %f not found", x);
    delete[] a;
    return 0;
}

bool binSearch(const float* a, int n, float x, int* idx) {
    if (n <= 0 || x <= a[0]) {
        *idx = 0;
        return (
            n > 0 &&
            x >= a[0] // x == a[0]
            );
    } else if (x > a[n-1]) {
        *idx = n;
        return false;
    } else {
        assert(
            n > 0 &&
            x > a[0] &&
            x <= a[n - 1]
        );
        int beg = 0;
        int end = n - 1;
        assert(
            a[beg] < x &&
            x <= a[end]
        );
        while (end - beg > 1) {
            int c = (end + beg) / 2;
            assert(
                beg < c &&
                c < end
            );
            if (a[c] < x) {
                beg = c;
            } else if (a[c] > x) {
                end = c;
            } else {
                // assert (a[c] == x)
                *idx = c;
                return true;
            }

        }
        assert(
            end - beg <= 1 &&
            a[beg] < x &&
            x <= a[end]
        );
        *idx = end;
        return (x >= a[end]);
    }
    return false;
}

void print(float*a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%lf ",a[i]);
    }
    printf("\n");
}

