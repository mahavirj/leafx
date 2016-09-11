#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct node_t {
	int data;
	struct node_t *next;
} node_t;

node_t *create_list(int no_elements);
node_t *create_sorted_list(int no_elements);
void free_list(node_t *list);
void print_list(node_t *list);

#endif
