#include <stdio.h>
#include <assert.h>

#pragma warning(disable : 4996)

int getFileLength(FILE*);
int* readFromFile(FILE*, int);
void writeInFile(FILE*, int*, int);
void shift(int*, int);
void reverse(int*, int);
void shiftRight(int*, int, int);
void print(int*, int);

int main(int argc, char* argv[])
{
    FILE* in = fopen("../cyclically_shift_array/in.txt", "r");
    if (in == NULL) {
        perror("Can't open a file");
        fclose(in);
        return -1;
    }
    int n = getFileLength(in);
    int* a = readFromFile(in,n);
    print(a, n);
    shift(a, n);
    print(a, n);
    shiftRight(a, n, 4);
    print(a, n);
    FILE* out = fopen("../cyclically_shift_array/out.txt", "w");
    if (out == NULL) {
        perror("Can't open a output file");
        fclose(out);
        return -1;
    }
    writeInFile(out, a, n);
    delete[] a;
    return 0;
}

int* readFromFile(FILE* f,int n) {
    rewind(f);
    int* a{ new int[n]};
    int x, m = 0;
    while (m < n) {
        if (fscanf(f, "%d", &x) < 1) {
            perror("Read error"); 
            fclose(f);
            return NULL;
        }
        a[m] = x; m++;
    }
    fclose(f);
    assert(n == m && n > 0);
    return a;
}

void writeInFile(FILE* f, int* a, int n) {
    for (int i = 0; i < n; ++i) {
        fprintf(f, "%d ", a[i]);
        if ((i + 1) % 10 == 0) fprintf(f, "\n");
    }
    fclose(f);
}

int getFileLength(FILE* f) {
    int n = 0;
    int x;
    while (fscanf(f, "%d", &x) == 1) {
        ++n;
    }
    if (n <= 0) {
        fprintf(stderr, "empty input file\n");
        return NULL;
    }
    return n;
}

void shift(int* a, int n) {
    if (n <= 0) return;
    int last = a[n - 1];
    for (int i = n-1; i > 0; --i){
        a[i] = a[i - 1];
    }
    a[0] = last;
}

void reverse(int* a, int n) {
    if (n <= 0) return;
    int i = 0, j = n-1;
    while (i < j) {
        // swap a[i] a[j]
        int tmp = a[i]; a[i] = a[j]; a[j] = tmp;
        ++i; --j;
    }
}

void shiftRight(int* a, int n, int k) {
    if (n <= 0 || k == 0) return;
    reverse(a, n-k);
    reverse(a+n-k, k);
    reverse(a, n);
}

void print(int* a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%3d", a[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");
}
