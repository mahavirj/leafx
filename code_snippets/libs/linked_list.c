#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"

typedef struct queue {
	int *q;
	int rd;
	int wr;
	int size;
} queue_t;

static queue_t queue1, queue2;

static void queue_init(queue_t * q)
{
	q->rd = 0;
	q->wr = 0;
}

static int en_queue(queue_t * q, int value)
{
	if (q->wr == q->size) {
		printf("queue full %d\n", value);
		return -1;
	}

	q->q[(q->wr)++] = value;
	return 0;
}

static int de_queue(queue_t * q)
{
	if (q->wr == q->rd) {
		printf("queue empty\n");
		return -1;
	}
	return q->q[(q->rd)++];
}

static int empty_queue(queue_t * q)
{
	return q->wr == q->rd ? 1 : 0;
}

static int head_queue(queue_t * q)
{
	return q->q[q->rd];
}

static void merge(node_t *p, int low, int middle, int high)
{
	int i;
	queue_t *q1 = &queue1;
	queue_t *q2 = &queue2;
	node_t *t = p;

	queue_init(q1);
	queue_init(q2);

	i = low;
	while (i--)
		t = t->next;

	for (i = low; i <= middle; i++) {
		en_queue(q1, t->data);
		t = t->next;
	}

	for (i = middle + 1; i <= high; i++) {
		en_queue(q2, t->data);
		t = t->next;
	}

	t = p;
	i = low;
	while (i--)
		t = t->next;

	while (!(empty_queue(q1) || empty_queue(q2))) {
		if (head_queue(q1) < head_queue(q2)) {
			t->data = de_queue(q1);
			t = t->next;
		} else {
			t->data = de_queue(q2);
			t = t->next;
		}
	}

	while (!(empty_queue(q1))) {
		t->data = de_queue(q1);
		t = t->next;
	}
	while (!(empty_queue(q2))) {
		t->data = de_queue(q2);
		t = t->next;
	}
}

static int _merge_sort(node_t *p, int low, int high)
{
	int middle;
	
	if (low < high) {
		middle = (low + high) / 2;
		_merge_sort(p, low, middle);
		_merge_sort(p, middle + 1, high);
		merge(p, low, middle, high);
	}

	return 0;
}

int merge_sort(node_t *p, int low, int high)
{
	queue1.q = (int *) malloc(sizeof(int) * (((high - low) / 2) + 1));
	queue2.q = (int *) malloc(sizeof(int) * (((high - low) / 2) + 1));

	if (!queue1.q || !queue2.q)
		return -1;

	queue1.size = queue2.size =((high - low) / 2) + 1;
	_merge_sort(p, low, high);

	free(queue1.q);
	free(queue2.q);
	return 0;
}

static node_t *create_node()
{
	node_t *n = (node_t *) malloc(sizeof(node_t));
	if (!n) {
		perror("malloc failed");
		return NULL;
	}
	return n;
}

node_t *create_list(int no_elements)
{
	int i;
	node_t *n, *head = NULL;

	for (i = 0; i < no_elements; i++) {
		n = create_node();
		n->data = random() % 1024;
		n->next = head;
		head = n;
	}

	return head;
}

static int insert_sorted_order(node_t **head, node_t *node)
{
	/* 1. Handles null linked list condition
	 * 2. Handles first node insert condition
         */
	if ((*head) == NULL || (*head)->data > node->data) {
		node->next = *head;
		*head = node;
	} else {
		node_t *tmp = *head;
		/* 3/4. Handles middle and tail insert */
		while ((tmp->next != NULL) && (tmp->next->data < node->data))
			tmp = tmp->next;

		node->next = tmp->next;
		tmp->next = node;
	}
	return 0;
}

static int sort_list(node_t **head)
{
	node_t *sorted = NULL;
	node_t *temp = *head;

	while (temp != NULL) {
		node_t *store = temp;
		temp = temp->next;
		insert_sorted_order(&sorted, store);
	}

	*head = sorted;
	return 0;
}

node_t *create_sorted_list(int no_elements)
{
	node_t *n = create_list(no_elements);

	/* O(n^2) vs O(nlogn) complexity */
#if 0
	/* Additional O(n) space required, as data is flipped and not nodes */
	merge_sort(n, 0, no_elements - 1);
#else
	sort_list(&n);
#endif
	return n;
}

void free_list(node_t *list)
{
	node_t *t;

	while (list) {
		t = list;
		list = list->next;
		free(t);				
	}	
}

void print_list(node_t *list)
{
	int i;

	printf("\nLinked list contents:\n");
	i = 0;
	while (list) {
		if (i && ((i % 16) == 0))
			printf("\n");
		printf("%04d ", list->data);
		list = list->next;
		++i;
	}
	printf("\nTotal elements: %d\n", i);	
}
