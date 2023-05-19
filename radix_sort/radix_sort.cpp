#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void convert(int*, int);
void countingSort(int*, int, int);
int getMax(int*, int);
int* fill(int);
void print(int*, int);

int main()
{
    int n = 10;
    int* a = fill(n);
    print(a, n);
    convert(a, n);
    print(a, n);
    delete[] a;
    return 0;
}
int* fill(int n) {
    int* a{ new int[n] };
    for (int i = 0; i < n; ++i) a[i] = (int)(rand() % 100);
    return a;
}
void convert(int* a, int n) {
    // Get maximum element
    int max = getMax(a, n);

    // Apply counting sort to sort elements based on place value.
    for (int place = 1; max / place > 0; place *= 10)
        countingSort(a, n, place);
}
// Using counting sort to sort the elements in the basis of significant places
void countingSort(int* a, int n, int place) {
    int* output{ new int[n + 1] };
    int max = (a[0] / place) % 10;

    for (int i = 1; i < n; i++) {
        if (((a[i] / place) % 10) > max)
            max = a[i];
    }
    int* count{ new int[max + 1] };

    for (int i = 0; i < max; ++i)
        count[i] = 0;

    // Calculate count of elements
    for (int i = 0; i < n; i++)
        count[(a[i] / place) % 10]++;

    // Calculate cumulative count
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Place the elements in sorted order
    for (int i = n - 1; i >= 0; i--) {
        output[count[(a[i] / place) % 10] - 1] = a[i];
        count[(a[i] / place) % 10]--;
    }

    for (int i = 0; i < n; i++)
        a[i] = output[i];
}
// Function to get the largest element from an array
int getMax(int* a, int n) {
    int max = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}
void print(int* a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%5.1d ", a[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
}
