/* Merge 2 sorted linked lists */

#include <stdio.h>
#include <linked_list.h>

node_t *merge_sorted_list(node_t *a, node_t *b)
{
	node_t *t, *fetch, *head;

	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;

	if (a->data < b->data) {
		head = t = a;
		a = a->next;
	} else {
		head = t = b;
		b = b->next;
	}

	while (a && b) {
		if (a->data < b->data) {
			fetch = a;
			a = a->next;
			t->next = fetch;							
		} else {
			fetch = b;
			b = b->next;	
			t->next = fetch;
		}
		t = t->next;
	}

	if (a)
		t->next = a;
	else if (b)
		t->next = b;

	return head;
}

int main(void)
{
	node_t *a = create_sorted_list(3200);
	node_t *b = create_sorted_list(1600);

	print_list(a);
	print_list(b);

	node_t *c = merge_sorted_list(a, b);

	print_list(c);
	free_list(c);
	/* No need to free a/b, already merged in c */
	return 0;
}
