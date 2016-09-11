/* First iteration remove 1,3,5,7...*/
/* Second iteration remove 2,4,6,8...*/

#include <stdio.h>

#define NUM (1024)
static int arr[NUM];

int main()
{
	int i, j;

	for (i = 0; i < NUM; i++)
		arr[i] = i + 1;

	for (i = NUM / 2; i; i /= 2) {
		for (j = 0; j < i; j++) {
			arr[j] = arr[2*j + 1];
		}
	}
		
	printf("last to survice value is %d\n", arr[0]);
	return 0;
}
