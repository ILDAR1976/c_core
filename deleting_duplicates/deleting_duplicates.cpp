#include <stdio.h>
#include <assert.h>

#pragma warning(disable : 4996)

int getFileLength(FILE*);
int* readFromFile(FILE*, int);
void heapSort(int*, int);
void sieve(int*, int, int);
void swap(int*, int*);
void elementsSet(int*, int, int*);
void elementsSet2(int*, int, int*);
bool binSearch(const int*, int, int, int*);
void writeInFile(FILE*, int*, int);
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
    int* a = readFromFile(in, n);
    print(a, n);
    elementsSet2(a, n, &n);
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

int* readFromFile(FILE* f, int n) {
    rewind(f);
    int* a{ new int[n] };
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

void heapSort(int* a, int n) {
    //step 1: pyramid building
    int k = n / 2; //k has no children
    while (k > 0) {
        //invariant: |   ...     : |piramyd ...   |
        //                      k
        --k;
        sieve(a, n, k);
    }
    //step 2:sorting by pyramid
    k = n;
    while (k > 1) {
        //invariant: | piramyd  ...     : |sorted...   |
        //                               k
        //elements a[0],...,a[n-1] - pyramyd
        //a[r] <= a[k+1] <= ... <= a[n-1]
        // a[i] <= a[k] at i < k
        --k;
        swap(&(a[0]), &(a[k]));
        sieve(a, k, 0);
    }
}

void sieve(int* a, int n, int i) {
    //i - index of the sieved element
    while (true) {
        int s0 = 2 * i + 1;
        if (s0 >= n) break;
        int s1 = s0 + 1;
        int s = s0;
        if (s1 < n && a[s1] > a[s0]) s = s1;
        if (a[i] >= a[s]) break;
        swap(&(a[i]), &(a[s]));
        //Going down the tree
        i = s;
    }

}

void swap(int* x, int* y) {
    int tmp = *x;
    *x = *y; *y = tmp;
}

void elementsSet(int* a, int n, int* m) {
    heapSort(a, n);
    int k = 0; // the number of different elements 
               // in the viewed part of the array
    for (int i = 0; i < n; ++i) {
        if (k == 0 || a[i] > a[k-1]) {
            if (i > k) {
                a[k] = a[i]; 
            }
            ++k;
        }
    }
    *m = k;
}

void elementsSet2(int* a, int n, int* m) {
    int k = 0;
    for (int i = 0; i < n; ++i) {
        int x = a[i];
        int idx;
        if (!binSearch(a, k, x, &idx)) {
            for (int j = k; j > idx; --j)
                a[j] = a[j - 1];
            a[idx] = x;
            ++k;
        }
    }
    *m = k;
}

bool binSearch(const int* a, int n, int x, int* idx) {
    if (n <= 0 || x <= a[0]) {
        *idx = 0;
        return (
            n > 0 &&
            x >= a[0] // x == a[0]
            );
    }
    else if (x > a[n - 1]) {
        *idx = n;
        return false;
    }
    else {
        assert(
            n > 0 &&
            x > a[0] &&
            x <= a[n - 1]
        );
        int beg = 0;
        int end = n - 1;
        assert(
            a[beg] < x &&
            x <= a[end]
        );
        while (end - beg > 1) {
            int c = (end + beg) / 2;
            assert(
                beg < c&&
                c < end
            );
            if (a[c] < x) {
                beg = c;
            }
            else if (a[c] > x) {
                end = c;
            }
            else {
                // assert (a[c] == x)
                *idx = c;
                return true;
            }

        }
        assert(
            end - beg <= 1 &&
            a[beg] < x &&
            x <= a[end]
        );
        *idx = end;
        return (x >= a[end]);
    }
    return false;
}

void print(int* a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%3d", a[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");
}
