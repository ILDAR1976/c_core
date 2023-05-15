#include <stdio.h>

int gcdExt(int,int,int*,int*);


int main()
{
    // The recursive extended Euclidean algorithm
    // -----------------------------------------------
    // It is known from the course of number theory 
    // that the greatest common divisor is expressed 
    // by gcd(m,n) as a linear combination of integers 
    // m and n. Let d = gcd(m,n), then d = u*m + v*n,
    // where m,n belong to the set of integers.
    int m, n;
    printf("Enter 2 numbers:\n");
    scanf_s("%d%d", &m, &n);
    int u, v;
    int d = gcdExt(m, n, &u, &v);
    printf("Ext gcd=%d u=%d v=%d", d, u, v);
    return 0;
}

int gcdExt(int m, int n, int* u, int* v) {
    if (n == 0) {
        *u = 1; *v = 0;
        return m;
    }
    int q = m / n; int r = m % n;
    int u1, v1;
    int d = gcdExt(n, r, &u1, &v1);
    *u = v1; *v = u1 - v1 * q;
    return d;
}