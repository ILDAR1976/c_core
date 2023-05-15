#include <stdio.h>

int main()
{
    int n;
    scanf_s("%d", &n);
    for (int i = 1; i <= n; ++i) {
        printf("%d ", i * i);
        if (i % 10 == 0) printf("\n");
    }
    printf("\n");
    return 0;
}