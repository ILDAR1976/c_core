#include <stdio.h>

int main()
{
    float f;
    double d;
    int* p, * p1;
    int s, e, mf, res;
    int md[2];
    while (true){
        printf("Input a real number:\n");
        res = scanf_s("%lf", &d);
        if (res <= 0) break;
        f = (float) d;
        // float ---------------------
        printf("Float representation:\n");
        p = (int*) &f;
        printf("Hex: %08x\n", *p);

        s = ((*p >> 31) & 1);
        e = ((*p >> 23) & 0xff);
        mf = (*p & 0x7fffff);

        printf("s=%d, e=%d, \nm=", s, e);
        unsigned int mask = 0x400000;
        while (mask != 0) {
            if ((mask & mf) != 0)
                printf("1");
            else
                printf("0");
            mask >>= 1;
        }
        printf("\n");

        // Double --------------------------
        printf("Double representaion:\n");
        p = (int*)&d; // Lower word
        p1 = p + 1;   // Upper word
        
        printf("Hex: %08x %08x\n", *p1, *p);
        s = ((*p1 >> 31) & 1);
        e = ((*p1 >> 20) & 0x7ff); // 11 bits
        md[0] = (*p1  & 0xfffff);    // 20 upper bits
                                   //     of mantissa
        md[1] = *p;                // 32 lower bits   

        printf("s=%d, e=%d, \nm=", s, e);
        mask = 0x80000;
        while (mask != 0) {
            if ((mask & md[0]) != 0)
                printf("1");
            else
                printf("0");
            mask >>= 1;
        }
        mask = 0x80000000;
        while (mask != 0) {
            if ((mask & md[1]) != 0)
                printf("1");
            else
                printf("0");
            mask >>= 1;
        }
        printf("\n");
    }
    return 0;
}