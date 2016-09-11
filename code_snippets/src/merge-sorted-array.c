#include <stdio.h>

int a[32] = {1, 3, 5, 7, 9};
int b[] = {2, 4, 6, 8, 10};

int merge_array(int *a, int n, int *b, int m)
{
	while (n && m) {
		if (a[n-1] < b[m-1]) {
			a[n+m-1] = b[m-1];
			--m;
		} else if (a[n-1] >= b[m-1]) {
			a[n+m-1] = a[n-1];
			--n;
		}
	}

	while (m) {
		a[n+m-1] = b[m-1];
		--m;
	}
	return 0;
}

int main(void)
{
	int n, m, i;
	n = m = 5;

	merge_array(a, n, b, m);

	for (i = 0; i < n+m-1; i++)
		printf("Final arr is %d\n", a[i]);
	return 0;
}
