#include <stdio.h>
#include <assert.h>

int extGcd(int, int, int*, int*);

int main()
{
    int m, n;
    printf("Enter m,n:\n");
    scanf_s("%d%d", &m, &n);
    int u, v, d;
    d = extGcd(m, n, &u, &v);
    printf("gcd:%d u=%d,v=%d",d,u,v);
    return 0;
}

int extGcd(int m, int n, int* u, int* v) {
    int a = m, b = n, u1 = 1, v1 = 0,  u2 = 0, v2 = 1;
    assert(
        a == u1 * m + v1 * n &&
        b == u2 * m + v2 * n
    );
    while (b != 0){
        // invariant: gcd(m,n) == gcd (a,b)
        int q = a / b, r = a % b;
        a = b; b = r;
        
        int tmp = u2;
        u2 = u1 - q * u2; u1 = tmp;

        tmp = v2;
        v2 = v1 - q * v2; v1  = tmp;
    }
    *u = u1; *v = v1;
    return a;
    
}