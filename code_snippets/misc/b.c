#define PADDING
#include "a.h"

int func(test_struct_t test)
{
	printf("MJ size here is %d %p %p\n", sizeof(test), test.num, &test.num);
	memset(&test.padding, 0, 16);
	return;
}
