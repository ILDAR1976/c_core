#include <stdio.h>

int gcd(int, int);

int main()
{
    printf("The greatest common divisior: %d", gcd(2023, 7));
}

int gcd(int m, int n) {
    if (n == 0) return m;
    int r = m % n;
    // gcd(m,n) = gcd(n,r)
    return gcd(n, r);
}
