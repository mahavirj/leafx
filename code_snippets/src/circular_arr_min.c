/*! Circular sorted array search minimum element
 *
 * Consider an array of n sorted elements in increasing order and it is
 * rotated by k where k is unknown, our goal is to find minimum element
 * in the array with log(n) complexity.
 * 
 * Key points:
 * 1. Each individual sub-arrays around k are sorted in themselves
 * 2. Minimum element from first array can be used as key to decide in which
 *    part(two equal halves) to further continue the search
 * 3. At any point of element is less than its previous element then that
 *    ends search process
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024
int arr[MAX_SIZE];

int min_search(int *arr, int low, int high, int key)
{
	if (high < low)
		return 0;

	int middle = (high + low) / 2;

	if (arr[middle] < arr[middle-1])
		return middle;

	if (arr[middle] >= key) {
		return min_search(arr, middle+1, high, key);
	} else {
		return min_search(arr, low, middle-1, key);
	}
}

int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int main()
{
	int i, ret;

	for (i = 0; i < MAX_SIZE; i++)
		arr[i] = rand() % MAX_SIZE;
	qsort(arr, MAX_SIZE, sizeof(int), compare);

	for (i = 0; i < MAX_SIZE; i++) {
		/* Circular shift by 1 element for each iteration */
		int temp = arr[0];
		memmove(arr, &arr[1], (MAX_SIZE-1) * sizeof(int));
		arr[MAX_SIZE-1] = temp;
		ret = min_search(arr, 0, MAX_SIZE-1, arr[0]);
		printf("found at %d\n", ret);
	}

	return 0;
}
