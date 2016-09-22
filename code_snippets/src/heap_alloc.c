/* Tiny mem allocator */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	size_t size;
	struct node *next;
	struct node *prev;
} node_t;

static node_t *start;
static int free_size;

#define MEM_SIZE (1UL << 10 << 10)
#define ALLOCATE (1UL << 31)

#define INIT_LIST_HEAD(head) ({ \
	(head)->next = NULL; \
	(head)->prev = NULL; \
})

static void insert_node(node_t *prev, node_t *new, node_t *next)
{
	new->next = next;
	new->prev = prev;
	if (prev)
		prev->next = new;
	if (next)
		next->prev = new;
}

static void remove_node(node_t **head, node_t *node)
{
	node_t *t = *head;

	if (t == node) {
		t->next->prev = t->prev;
		*head = t->next;
	} else {
		t = t->next;
		while (t) {
			if (t == node) {
				t->prev->next = t->next;
				if (t->next)
					t->next->prev = t->prev;
				break;
			}
			t = t->next;
		}
	}
}

void tiny_free(void *addr)
{
	node_t *t = (node_t *) ((size_t) addr - sizeof(node_t));
	node_t *it = start;

	if (!(t->size & (1UL << 31))) {
		printf("Err...unallocated block\n");
		return;
	}

	t->size &= ~(ALLOCATE);
	free_size += t->size;

	if (t->size < it->size) {
		t->prev = it->prev;
		t->next = it;
		it->prev = t;
		start = t;
	} else {
		while (it->next && t->size > it->next->size)
			it = it->next;
		insert_node(it, t, it->next);
	}
}

void *tiny_malloc(size_t size)
{
	node_t *it = start;

	size += sizeof(node_t);
	if (size > free_size) {
		printf("Err...no more memory\n");
		return NULL;
	}

	while (it) {
		if (it->size >= size) {
			if (it->size > size) {
				/* Found large enough block */
				node_t *next = (node_t *) ((size_t) it + size);
				next->size = it->size - size;
				insert_node(it, next, it->next);
			}
			it->size = size | ALLOCATE;
			remove_node(&start, it);
			free_size -= size;
			return (void *) ((size_t) it + sizeof(node_t));
		}

		it = it->next;
	}

	return NULL;
}
	
int mem_init(size_t size)
{
	char *mem_start = (char *) malloc(size);
	if (!mem_start) {
		perror("malloc failed");
		return -1;
	}
	printf("MEM: start addr %p\n", mem_start);

	start = (node_t *) mem_start;
	start->size = size;
	INIT_LIST_HEAD(start);
	free_size = size;
	return 0;
}

int main(void)
{
	int ret;
	char *addr[5];

	mem_init(MEM_SIZE);

	int i = 0;
	while (1) {
		addr[0] = tiny_malloc(1 << 10 << 2);
		if (!addr[0])
			break;
		printf("MEM: allocated %p %d\n", addr[0], ++i);
	}

#if 0
	addr[0] = tiny_malloc(1024);
	printf("MEM: allocated %p\n", addr[0]);
	addr[1] = tiny_malloc(512);
	printf("MEM: allocated %p\n", addr[1]);
	addr[2] = tiny_malloc(256);
	printf("MEM: allocated %p\n", addr[2]);
	addr[3] = tiny_malloc(128);
	printf("MEM: allocated %p\n", addr[3]);
	addr[4] = tiny_malloc(64);
	printf("MEM: allocated %p\n", addr[4]);

	tiny_free(addr[0]);
	tiny_free(addr[1]);
	tiny_free(addr[2]);
	tiny_free(addr[3]);
	tiny_free(addr[4]);

	addr[0] = tiny_malloc(1024);
	printf("MEM: allocated %p\n", addr[0]);
	addr[1] = tiny_malloc(512);
	printf("MEM: allocated %p\n", addr[1]);
	addr[2] = tiny_malloc(256);
	printf("MEM: allocated %p\n", addr[2]);
	addr[3] = tiny_malloc(128);
	printf("MEM: allocated %p\n", addr[3]);
	addr[4] = tiny_malloc(64);
	printf("MEM: allocated %p\n", addr[4]);
#endif
	return 0;
}
