#include <stdio.h>

int gcd(int, int);

int main()
{
    int m = 12;
    int n = 16;

    int c = gcd(m, n);

    printf("The greatest common devisor: %d", c);

    return 0;
}

int gcd(int m, int n) {
    // The Euclidean algorithm
    int r;
    while (n != 0) {
        r = m % n;
        m = n; n = r;
    }
    // n == 0 and gcd (m,n) = gcd(m0,n0)
    return m;
}

