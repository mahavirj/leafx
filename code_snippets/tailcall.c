#include <stdio.h>

int bar(int val)
{
	volatile int cnt;
	cnt = val;
	while (cnt--)
		;
	return;
}

int foo(int val)
{
	bar(val);
	return;
}

int main()
{
	foo(10);
	return 0;
}
