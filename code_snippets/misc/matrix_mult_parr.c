
#include <stdio.h>

#define M (1024)
static int a[M][M];
static int b[M][M];
static int c[M][M];

int main(void)
{
	int i, j, k;

#pragma omp parallel for default(shared) private(i, j, k)
	for (i = 0; i < M; i++) {
		for (j = 0; j < M; j++) {
			for (k = 0; k < M; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
	
	return 0;
}
