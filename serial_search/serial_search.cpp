#include <stdio.h>
#include <cstdlib>

bool serSearch(const double*, int, double, int*);

int main()
{
	double *a = { new double[10] };
	double x;
	int n;
	int idx = 0; 
	printf("Enter found number:\n");
	scanf_s("%lf", &x);

	printf("Enter sequence of number:\n");
	for (n = 0; n < 10;++n) {
		scanf_s("%lf", &a[n]);
	}
	if (serSearch(a, n, x, &idx))
		printf("The number %lf is founded, its index is %d\n",x, idx);
	else
		printf("The number %lf is not found\n",x);
	delete[] a;
    return 0;
}


bool serSearch(const double* a, int n, double x, int* idx) {
	const double EPS = 1.e-6;
	bool found = false;
	for (int i = 0; !found && i < n; ++i) {
		if (fabs(a[i] - x) <= EPS) {
			found = true;
			*idx = i;
		}
	}
	return found;
}
