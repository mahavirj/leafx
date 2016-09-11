/* Find and Delete stack mid in O(1) */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

typedef int item_t;

typedef struct stack_t {
	item_t data;
	list_head_t node;	
} stack_t;

typedef struct stack_super_t {
	int count;
	list_head_t head;
	list_head_t *mid;
} stack_super_t; 

item_t mid(stack_super_t *s)
{
	if (!s->mid)
		return -1;

	stack_t *st = list_entry(s->mid, stack_t, node);
	return st->data;
}

int push(stack_super_t *s, item_t val)
{
	stack_t *st = (stack_t *) malloc(sizeof(stack_t));
	if (!st)
		return -1;

	st->data = val;
	list_add(&st->node, &s->head);
	++s->count;
	if (s->count == 1)
		s->mid = &st->node;
	else if (s->count & 0x1)
		s->mid = s->mid->prev;

	return 0;
}

item_t pop(stack_super_t *s)
{
	if (list_empty(&s->head))
		return -1;

	stack_t *st = list_first_entry(&s->head, stack_t, node);
	--s->count;
	if (s->count == 0)
		s->mid = NULL;
	else if (!(s->count & 0x1))
		s->mid = s->mid->next;

	item_t val = st->data;
	list_del(&st->node);
	free(st);

	return val;
}

int main()
{
	int i;
	stack_super_t s;

	memset(&s, 0, sizeof(s));
	INIT_LIST_HEAD(&s.head);
	
	push(&s, 10);
	printf("mid of stack is %d\n", mid(&s));
	push(&s, 11);
	printf("mid of stack is %d\n", mid(&s));
	push(&s, 12);	
	printf("mid of stack is %d\n", mid(&s));
	push(&s, 13);	
	printf("mid of stack is %d\n", mid(&s));
	push(&s, 14);	
	printf("mid of stack is %d\n", mid(&s));

	for (i = 0; i < 5; i++) {
		printf("Value from stack is %d\n", pop(&s));
		printf("mid of stack is %d\n", mid(&s));
	}

	return 0;
}
