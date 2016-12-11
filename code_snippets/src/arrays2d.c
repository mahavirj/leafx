
#include <stdio.h>

#define R 3
#define C 4

int main(void)
{
	int **arr;

	arr = malloc(R * sizeof(int *));
	if (!arr)
		perror("malloc failed");
	
	int i, j;
	for (i = 0; i < R; i++)
		arr[i] = malloc(C * sizeof(int));


	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			arr[i][j] = j;
		}
	}
		
	for (i = 0; i < R; i++)
		free(arr[i]);
	free(arr);
}
