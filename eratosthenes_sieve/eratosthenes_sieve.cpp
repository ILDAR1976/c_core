#include <stdio.h>

void sieve(int);

int main()
{
    int n;
    printf("Enter n:\n");
    scanf_s("%d", &n);
    sieve(n);
    return 0;
}

void sieve(int n) {
    bool* a = new bool[n + 1];
    for (int i = 0; i <= n; ++i) a[i] = true;
    a[0] = false;
    a[1] = false;
    int i,p = 2;
    while (p < n) {
        i = p + p;
        while (i <= n) {
            a[i] = false;
            i += p;
        }
        ++p;
        while (p <= n && !a[p]) ++p;
    }
    int numPrimes = 0;
    for (int i = 0; i <= n; ++i) {
        if (a[i]) {
            printf("%d ", i);
            if (numPrimes > 0) {
                if (numPrimes % 10 == 0) {
                    printf("\n");
                }
            }
            numPrimes++;
        }
    }
    if (numPrimes % 10 != 0) printf("\n");
    printf("Quantity of prime numbers is %d", numPrimes);
}
