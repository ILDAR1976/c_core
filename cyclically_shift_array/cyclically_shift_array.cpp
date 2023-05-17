#include <stdio.h>
#include <assert.h>

#pragma warning(disable : 4996)

int getFileLength(FILE*);
int* readFromFile(FILE*, int);
void writeInFile(FILE*, int*, int);
int gcd(int, int);
void shift(int*, int);
void reverse(int*, int);
void shiftRight(int*, int, int);
void shiftRight2(int*, int, int);
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
    shiftRight2(a, n, 4);
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

int gcd(int m, int n) {
    // The Euclidean algorithm
    int r;
    while (n != 0) {
        r = m % n;
        m = n; n = r;
    }
    // n == 0 and gcd (m,n) = gcd(m0,n0)
    return m;
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

// To understand this function you need to know
// elementary number theory
void shiftRight2(int* a, int n, int k) {
    // Idea: starting from an element with
    // index 0 and running its orbit while mapping 
    // the indices s: i |--> (i+k) (mod n)
    // --------------------------------------------
    // the number of orbits is equal to the minimal 
    // nonzero index in the orbit of the element 0
    // --------------------------------------------
    // any permutation is decomposed into a product 
    // of independent cycles
    // --------------------------------------------
    // permutation is a one - to - one mapping of 
    // elements 0, 1, 2, ..., n - 1.
    // s is represented as a product of d cycles 
    // of length n / d.
    // d = gcd(n, k)
    // Elements of the orbit differ by numbers of 
    // the form un + vk, where u, n belong to Z.
    // I = { un + vk, where u, n belong to Z } is 
    // an ideal in the ring Z which has the form d * Z.
    // Indexes 0,1,2,...,d-1 generate different orbits.
    k %= n;
    if (n <= 0 || k == 0) return;
    int nod = gcd(n, k);
    int i = 0;
    while (i < nod) { // orbital cycle
        //pass the orbit of the element i
        int x = a[i]; // initial orbit element
        int j = i + k;
        if (i > n) j -= n;
        while (i != j)  {
            int y = a[j];
            a[j] = x;
            x = y;
            j += k;
            if (j >= n) j -= n;
        }
        a[i] = x;
        ++i; // move on to the next orbit
    }
}

void print(int* a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%3d", a[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");
}
