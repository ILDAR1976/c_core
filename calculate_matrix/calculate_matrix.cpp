#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


int gaussMethod(int, int, double*, double);
void print(double*, int, int);

int main()
{
    int m, n, i, j, rank;
   
    double eps, det;

    printf("Input matrix size m,n: ");
    scanf_s("%d%d", &m, &n);

    double* a{ new double[(m * n)]};

    printf("Input matrix elements:\n");
    for ( i = 0; i < m; ++i){
        for (j = 0; j < n; ++j) {
            scanf_s("%lf", &(a[i * n + j]));
        }
    }
    
    printf("Enter the accuracy of the calculations eps: ");
    scanf_s("%lf", &eps);

    //call Gauss method
    rank = gaussMethod(m, n, a, eps);

    print(a, m, n);

    //print rank matrix
    printf("rank = %d\n", rank);

    if (m == n) {
        // For a square matrix, calculate and print its determinant
        det = 1.;
        for (i = 0; i < m; i++) {
            det *= a[i * n + i];
        }
        printf("Matrix determinant = %.3lf\n", det);
    }

    delete[] a; // clear dinamic memory
    return 0;
}

int gaussMethod(int m, int n, double* a, double eps) {
    int i, j, k, l;
    double r;

    i = 0; j = 0;
    while (i < m && j < n) {
        // Invariant: the matrix minor in columns 0...j-1
        // is already reduced to the step form, and 
        // its rank is equal to i
        //
        // look for the maximal element in the j-th column,
        // starting from the i-th row
        r = 0.0;
        for (k = i; k < m; ++k) {
            if (fabs(a[k * n + j]) > r) {
                l = k; //let's remember the line number
                r = fabs(a[k * n + j]); //and the maximal element
            }
        }
        if (r <= eps) {
            // all elements of the j-th column do
            //  not exceed eps in absolute value.
            // Let's zero the column starting from the i-th row
            for (k = i; k < m; ++k) {
                a[k * n + j] = 0.0;
            }
            ++j; //incremnt column index
            continue; // move on to the next operation
        }
        if (l != i) {
            // swap the i-th and l-th rows
            for (k = j; k < n; ++k) {
                r = a[i * n + k];
                a[i * n + k] = a[l * n + k];
                a[l * n + k] = (-r); //change the line sign
            }
        }

        //approval: fabs(a[i * n + j] > eps
        r = a[i * n + j];
        assert(fabs(r) > eps);

        for (k = i + 1; k < m; ++k) {
            double c = (-a[k * n + j]) / r;

            // We zero out the j-th column, 
            // starting from row i+l, applying
            // the elementary transformations of the 2nd kind

            a[k * n + j] = 0.0;
            for (l = j + 1; l < n; ++l) {
                a[k * n + l] += c * a[i * n + l];
            }
        }
        ++i; ++j; //move on to the next minor
    }
    return i; //return a non-zero number of lines
}

void print(double *a, int m, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%10.3lf ", a[i*n + j]);
        }
        printf("\n");
    }
}
