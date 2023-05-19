#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

char* convert(int);

void print(char*, int);

int main()
{
    int n = 1256789;
    print(convert(n), 32);
    return 0;
}

char* convert(int n) {
    int i = 32;
    char* t = new char[32];
    t[i] = 0;
    while (--i >= 0) {
        if ((n & 1) == 0) {
            t[i] = '0';
        } else {
            t[i] = '1';
        }
        n >>= 1;
    }
    return t;
}

void print(char* a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%c", a[i]);
    }
    printf("\n");
}
