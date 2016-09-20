
#include <stdio.h>
#include <stdint.h>

#if 0
int is_div_by_7(int no)
{
	if (no == 0)
		return 1;
	else if (no < 0)
		return 0;

	return is_div_by_7((int) (no >> 3) - (int) (no & 0x7));
}
#endif

int is_div_by_3(int no)
{
	if (no == 0)
		return 1;
	else if (no < 0)
		return 0;

	return is_div_by_3((int) (no >> 1) - (int) (no & 0x1));
}

int is_div_by_5(int no)
{
	if (no == 0)
		return 1;
	else if (no < 0)
		return 0;

	return is_div_by_5((int) (no >> 2) - (int) (no & 0x3));
}

int main(void)
{
	int i, res, res1, number;

	for (i = 0; i < 1024; i++) {
		number = rand() % 1024;
		res = number % 3 ? 0: 1;
		res1 = is_div_by_3(abs(number));
		if (res != res1) {
			printf("1. Test case failure for %d\n", number);
			return -1;
		}

		res = number % 5 ? 0: 1;
		res1 = is_div_by_5(abs(number));
		if (res != res1) {
			printf("2. Test case failure for %d\n", number);
			return -1;
		}
#if 0
		res = number % 7 ? 0: 1;
		res1 = is_div_by_7(abs(number));
		if (res != res1) {
			printf("3. Test case failure for %d\n", number);
			return -1;
		}
#endif
	}
	printf("Test case success\n");

	return 0;
}
