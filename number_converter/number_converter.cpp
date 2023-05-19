#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

const char* HEXDIGITS = new char[64]{
                       '0','1','2','3','4',
                       '5','6','7','8','9',
                       'A','B','C','D','E',
                       'F' };

char* convertToBin(int);
char* convertToHex(int);
void print(char*, int);

int main()
{
    int n = 1256789;
    printf("dec: %d\n", n);
    printf("bin: "); print(convertToBin(n), 64);
    printf("hex: "); print(convertToHex(n), 8);
    return 0;
}

char* convertToBin(int n) {
    //binary representaion
    int i = 64;
    char* t = new char[64];
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

char* convertToHex(int n) {
    //hex representation
    int i = 8;
    char* t = new char[8];
    
    while (--i >= 0) {
        int d = (n & 0xf);
        t[i] = HEXDIGITS[d];
        n >>= 4;
    }
    return t;
}

void print(char* a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%c", a[i]);
    }
    printf("\n");
}
