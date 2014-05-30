#include <stdio.h>

void bar(int val)
{
	volatile int cnt;
	cnt = val;
	while (cnt--)
		;
	return;
}

void foo(int val)
{
	bar(val);
	return;
}

int main()
{
	foo(10);
	return 0;
}
