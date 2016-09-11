
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_ITEM 64 * 1024

typedef struct list {
	int val;
	struct list *next;
} list_t;

static list_t *head;

typedef struct queue {
	int q[(MAX_ITEM / 2) + 1];
	int rd;
	int wr;
} queue_t;

static queue_t queue1, queue2;

void queue_init(queue_t * q)
{
	q->rd = 0;
	q->wr = 0;
}

int en_queue(queue_t * q, int value)
{
	if (q->wr == sizeof(q->q)) {
		printf("queue full %d\n", value);
		return -1;
	}

	q->q[(q->wr)++] = value;
	return 0;
}

int de_queue(queue_t * q)
{
	if (q->wr == q->rd) {
		printf("queue empty\n");
		return -1;
	}
	return q->q[(q->rd)++];
}

int empty_queue(queue_t * q)
{
	return q->wr == q->rd ? 1 : 0;
}

int head_queue(queue_t * q)
{
	return q->q[q->rd];
}

void merge(list_t *p, int low, int middle, int high)
{
	int i;
	queue_t *q1 = &queue1;
	queue_t *q2 = &queue2;
	list_t *t = p;

	queue_init(q1);
	queue_init(q2);

	i = low;
	while (i--)
		t = t->next;

	for (i = low; i <= middle; i++) {
		en_queue(q1, t->val);
		t = t->next;
	}

	for (i = middle + 1; i <= high; i++) {
		en_queue(q2, t->val);
		t = t->next;
	}

	t = p;
	i = low;
	while (i--)
		t = t->next;

	while (!(empty_queue(q1) || empty_queue(q2))) {
		if (head_queue(q1) > head_queue(q2)) {
			t->val = de_queue(q1);
			t = t->next;
		} else {
			t->val = de_queue(q2);
			t = t->next;
		}
	}

	while (!(empty_queue(q1))) {
		t->val = de_queue(q1);
		t = t->next;
	}
	while (!(empty_queue(q2))) {
		t->val = de_queue(q2);
		t = t->next;
	}
}

int m_sort(list_t *p, int low, int high)
{
	int middle;

	if (low < high) {
		middle = (low + high) / 2;
		m_sort(p, low, middle);
		m_sort(p, middle + 1, high);
		merge(p, low, middle, high);
	}
	return 0;
}

int insert_element(list_t **head, int value)
{
	if (!(*head)) {
		*head = (list_t *) malloc(sizeof(list_t));
		if (!(*head)) {
			perror("malloc failed\n");
			return -1;
		}
		(*head)->val = value;
		(*head)->next = NULL;
	} else {
		list_t *tmp = (list_t *) malloc(sizeof(list_t));
		if (!tmp) {
			perror("malloc failed\n");
			return -1;
		}
		tmp->val = value;
		tmp->next = (*head)->next;
		(*head)->next = tmp;
	}
	return 0;
}

int main()
{
	int i;
	list_t *node;

	for (i = 0; i < MAX_ITEM; i++)
		insert_element(&head, rand() % 100);

	printf("\nBefore sorting\n");
	node = head;
	while (node) {
		printf(" %d", node->val);
		node = node->next;
	}

	m_sort(head, 0, MAX_ITEM - 1);

	printf("\nAfter sorting\n");
	node = head;
	while (node) {
		printf(" %d", node->val);
		list_t *tmp = node;
		node = node->next;
		free(tmp);
	}

	return 0;
}
