#include <stdio.h>

int main()
{
	double s = 0, l = 0, e = 0, avg = 0;
	printf("Enter the members of the sequence\n");
	while (scanf_s("%lf",&e) == 1){
		s += e;
		l++;
	}
	avg = s / l;
	printf("Avg = %lf", avg);
	return 0;
}