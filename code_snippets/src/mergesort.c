
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_ITEM 64

static int m_arr[MAX_ITEM] = { 0, };

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

void merge(int *p, int low, int middle, int high)
{
	int i;
	queue_t *q1 = &queue1;
	queue_t *q2 = &queue2;

	queue_init(q1);
	queue_init(q2);

	for (i = low; i <= middle; i++)
		en_queue(q1, p[i]);

	for (i = middle + 1; i <= high; i++)
		en_queue(q2, p[i]);

	i = low;
	while (!(empty_queue(q1) || empty_queue(q2))) {
		if (head_queue(q1) > head_queue(q2))
			p[low++] = de_queue(q1);
		else
			p[low++] = de_queue(q2);
	}

	while (!(empty_queue(q1)))
		p[low++] = de_queue(q1);
	while (!(empty_queue(q2)))
		p[low++] = de_queue(q2);
}

int m_sort(int *p, int low, int high)
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

int main()
{
	int i;
	int *p = m_arr;

	for (i = 0; i < MAX_ITEM; i++)
		p[i] = rand() % 100;

	m_sort(p, 0, MAX_ITEM - 1);

	for (i = 0; i < MAX_ITEM; i++)
		printf("val is %d\n", p[i]);

	return 0;
}
