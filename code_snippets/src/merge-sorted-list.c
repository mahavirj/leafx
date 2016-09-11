/* Merge 2 sorted linked lists */

#include <stdio.h>
#include <linked_list.h>

node_t *merge_sorted_list(node_t *a, node_t *b)
{
	node_t temp; /* dummy anchor for merged list */
	node_t *t = &temp, *fetch;
	t->next = NULL;

	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;

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

	return temp.next;
}

int main(void)
{
	node_t *a = create_sorted_list(1600);
	node_t *b = create_sorted_list(3200);

	print_list(a);
	print_list(b);

	node_t *c = merge_sorted_list(a, b);

	print_list(c);
	free_list(c);
	/* No need to free a/b, already merged in c */
	return 0;
}
