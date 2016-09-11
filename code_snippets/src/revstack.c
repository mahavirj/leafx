#include <stdio.h>
#include <stdlib.h>

#define MAX_LIMIT 1024

static int index;
static int stack[MAX_LIMIT];

static int push(int data)
{
	if (index != MAX_LIMIT) {
		stack[index++] = data;
		return 0;
	}
	return -1;
}

static int pop()
{
	if (!index)
		return -1;
	return stack[--index];
}

static void dumpstack()
{
	int i;
	for (i = 0; i < index; i++)
		printf("Element is %x\n", stack[i]);
}

static void push_at_end(int data)
{
	if (!index) {
		push(data);
	} else {
		int temp;
		temp = pop();
		push_at_end(data);
		push(temp);
	}
}

static void revstack()
{
	int data;
	if (!index)
		return;
	data = pop();
	revstack();
	push_at_end(data);
}

int main()
{
	int cnt;
	for (cnt = 0; cnt < MAX_LIMIT; cnt++)
		push(cnt);
	printf("Original stack contents\n");
	dumpstack();
	revstack();
	printf("Reversed stack content\n");
	dumpstack();
	return 0;
}
