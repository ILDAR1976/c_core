#include <stdio.h>

const int MAX_PRIMES = 100000;
static int primes[MAX_PRIMES];
static int numPrimes = 0;

void job1();
void job2();
bool prime1(int);
void prime2(int,int);

int main()
{
    job1();
    return 0;
}
void job1() {
    int n, k, p;
    printf("Enter n:\n");
    scanf_s("%d", &n);
    k = 0;
    p = 2;
    printf("%d\t", p);
    ++k;
    p = 3;
    while (k < n) {
        if (prime1(p)) {
            printf("%d\t", p);
            ++k;
            if (k % 10 == 0)
                printf("\n");
        }
        p += 2;
    }
    printf("\n");
}
void job2() {
    int n, p;
    printf("Enter n:\n");
    scanf_s("%d", &n);
    if (n > MAX_PRIMES)
        n = MAX_PRIMES;
    
    primes[0] = 2;
    ++numPrimes;
    
    p = 3;
    prime2(p,n);
    
    for (int i = 0; i < numPrimes; ++i) {
        printf("%d ", primes[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
}
bool prime1(int p) {
    if (p < 2)
        return false;
    else if (p == 2)
        return true;
    else if (p % 2 == 0)
        return false;

    int d = 3;
    while (d*d <= p) {
        if (p % d == 0) {
            return false;
        }
        d += 2;
    }
    return true;
}
void prime2(int p,int n) {
    while (numPrimes < n) {
        bool prime = true;
        for (int i = 0; prime && i < numPrimes; ++i) {
            int d = primes[i];
            if (d * d > p)
                break;
            else if (p % d == 0)
                prime = false;
        }
        if (prime) {
            primes[numPrimes] = p;
            ++numPrimes;
        }
        p += 2;
    }
}
