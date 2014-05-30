/*
 * Feel Free To Re-distribute with credit to Author
 * Mahavir Jain <mahavirpj@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEM 63

typedef struct p_queue {
	int p[MAX_ITEM + 1];
	int val;
} p_queue_t;

static p_queue_t pg;

int pq_parent(p_queue_t *p, int index)
{	
	return (int) (index / 2);	
}

int pq_lchild(p_queue_t *p, int index)
{	
	return index * 2;	
}

void pq_swap(p_queue_t *p, int index1, int index2)
{
	int val;

	val = p->p[index1];
	p->p[index1] = p->p[index2];
	p->p[index2] = val;

	return;
}

/* Inserted element is at last and then restores order */
void bubble_up(p_queue_t *p, int value)
{
	int parent = pq_parent(p, value);	

	if (parent <= 0)
		return;

	if (p->p[parent] < p->p[value]) {
		pq_swap(p, value, parent);
		bubble_up(p, parent);
	}
}

void bubble_down(p_queue_t *p, int value)
{
	int c = pq_lchild(p, value);
	int m_index = value;

	int i;
	for (i = 0; i <= 1; i++) {
		if ((c + i) <= p->val) {
			if (p->p[m_index] < p->p[c + i])
				m_index = c + i;
		}
	}

	if (m_index != value) {
		pq_swap(p, value, m_index);
		bubble_down(p, m_index);
	}
}

int remove_min(p_queue_t *p)
{
	int result;

	if (p->val <= 0)
		return -1;

	result = p->p[1];
	p->p[1] = p->p[p->val];
	p->val--;
	bubble_down(p, 1);
	return result;
}

int insert(p_queue_t *p, int value)
{
	if (p->val >= MAX_ITEM)
		return -1;
	p->p[++(p->val)] = value;
	bubble_up(p, p->val);

	return 0;
}
	
int main(void)
{
	p_queue_t *p = &pg;

	memset(p, 0, sizeof(p_queue_t));

	/* Fill up and sort priority queue, O(n) time */
	int i;
	for (i = 1; i < MAX_ITEM + 1; i++)
		insert(p, rand() % 100);

	/* Extract minimu element from p_queue in log(n) time */
	for (i = 1; i < MAX_ITEM + 1; i++)
		printf("val is %d\n", remove_min(p));

	return 0;
}

