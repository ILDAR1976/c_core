#include <stdio.h>
#include <math.h>

int main()
{
    long long n, d, k;
    printf("Enter n:\n");
    scanf_s("%lld", &n);
    printf("Factorization of integer number:\n");
    d = 2; k = 0;
    while (d <= n) {
        if (n % d == 0) {
            printf("%lld ", d);
            ++k;   // number of prime factors
            n /= d;
        } else {
            if (d == 2)
                ++d;
            else
                d += 2;
        }
    }
    printf("\n");
    
    if (k == 1)
        printf("this number is prime");

    return 0;
}