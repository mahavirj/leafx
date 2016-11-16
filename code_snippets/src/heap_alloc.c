/* Tiny mem allocator
 *
 * First fit method for simplicity and less metadata overhead per node
 * Compaction for front and back merge supported in O(1)
 * Malloc/Free complexity of O(n) order for list traversal
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_DEBUG

#ifdef MEM_DEBUG
#define dbg printf
#else
#define dbg {}
#endif

typedef struct node {
	size_t size;
	struct node *next;
	/*
	 * For best fit case, next would be pointer to next free node as per
	 * size, and previous will also be required for node just previous to
         * ours based on address. This helps to identify merge conditions based
         * on node if free or not, without traversing entire list. Next node
         * based on address could be traced by adding size to current one.
         */
} node_t;

static node_t *start;
static size_t free_size;
static char *mem_start;
const int min_alloc_size = sizeof(node_t);

#define MEM_SIZE (1U << 10 << 10)
#define ALLOCATE (1U << 31)

void tiny_free(void *addr)
{
	node_t *new;
	node_t *current = start;

	if (!addr)
		return;

	new = (node_t *) ((size_t) addr - sizeof(node_t));
	if (!(new->size & ALLOCATE)) {
		printf("Err...unallocated block\n");
		return;
	}

	dbg("Freeing %p\n", addr);	

	new->size &= ~(ALLOCATE);
	free_size += new->size;

	/* Head null or insert after head condition handling */
	if (current == NULL || new < current) {
		if (((size_t) new + new->size) == (size_t) current) {
			new->size += current->size;
			new->next = current->next;
			start = new;
		} else {
			new->next = current;
			start = new;
		}
	} else {
		while (current->next && (current->next < new))
			current = current->next;

		/* Insert node anyways */
		new->next = current->next;
		current->next = new;

		/* Check for front merge */
		if (((size_t) new + new->size) == (size_t) new->next) {
			new->size += new->next->size;
			new->next = new->next->next;
		}

		/* Check for back merge */
		if (((size_t) current + current->size) == (size_t) new) {
			current->size += new->size;
			current->next = new->next;
		}
	}
}

void *tiny_malloc(size_t size)
{
	node_t *current = start;
	node_t *prev = current;

	size += sizeof(node_t);
	if (size > free_size) {
		printf("Err...no more memory\n");
		return NULL;
	}

	while (current) {
		if (current->size >= size) {
			if (current->size > (size + min_alloc_size)) {
				/* Found large enough block */
				node_t *new = (node_t *) ((size_t) current + size);
				new->size = current->size - size;
				new->next = current->next;
				current->next = new;
			} else {
				/* Size could be more than asked, as per min_alloc_size */
				size = current->size;
			}

			/* Mark as allocated node, size field is used 31st bit */
			current->size = size | ALLOCATE;
			/* See if head needs split */
			if (current == start)
				start = current->next;
			else
				prev->next = current->next;
			free_size -= size;
			dbg("Allocated 0x%x at %p\n", size - sizeof(node_t),
					 (void *) ((size_t) current + sizeof(node_t)));
			return (void *) ((size_t) current + sizeof(node_t));
		}
		prev = current;
		current = current->next;
	}

	dbg("Rquired size unable to allocate %d\n", size - sizeof(node_t));
	return NULL;
}
	
int mem_init(size_t size)
{
	mem_start = (char *) malloc(size);
	if (!mem_start) {
		perror("malloc failed");
		return -1;
	}
	printf("MEM: start addr %p\n", mem_start);

	start = (node_t *) mem_start;
	start->size = size;
	start->next = NULL;
	free_size = size;
	return 0;
}

void iterate_block_list(char *mem_start)
{
	node_t *current = (node_t *) mem_start;

	printf("\nAddress\t\tSize\t\tNext\t\tStatus\n");
	while ((size_t) current < (size_t) mem_start + MEM_SIZE) {
		printf("0x%08x\t0x%08x\t0x%08x\t%s\n",
			 (size_t) current, current->size & ~(ALLOCATE),
			 (size_t) current->next,
			 current->size & ALLOCATE ? "Alloc" : "Free");
		current = (node_t *) ((size_t) current +
					 (current->size & ~(ALLOCATE)));
	}
}

void *tiny_malloc_aligned(size_t size, int alignment)
{
	if (alignment & (alignment - 1)) {
		printf("Err...alignment not power of 2\n");
		return NULL;
	}

	/* size overhead due to alignment requirement */
	size_t alloc_size = (size + sizeof(void *) + (alignment - 1));
	void *addr = tiny_malloc(alloc_size);
	if (addr) {
		void *r_addr = (void *) (((size_t) addr + sizeof(void *) +
						 (alignment)) & ~(alignment - 1));
		*((void **) r_addr - 1) = addr;
		return r_addr;
	}
	return NULL;
}

void tiny_free_aligned(void *addr)
{
	tiny_free(*((void **)addr - 1));
	return;
}

#define SIZE (1U << 10 << 4)
int main(void)
{
	char *addr[SIZE];

	memset(addr, 0, sizeof(addr));
	mem_init(MEM_SIZE);

	char *a = tiny_malloc_aligned(32, 1024);
	char *b = tiny_malloc_aligned(23, 256);
	char *c = tiny_malloc_aligned(61, 64);
	char *d = tiny_malloc_aligned(60, 64);

	tiny_free_aligned(a);
	tiny_free_aligned(b);
	tiny_free_aligned(c);
	tiny_free_aligned(d);

	int lfree;
	int i = 0;
	while (i < SIZE) {
		int size = (rand() % 1024) + 1;
		addr[i] = tiny_malloc(size);
		if (!addr[i])
			break;;
		memset(addr[i], 0x55, size);
		if (free_size < MEM_SIZE / 2) {
			do {
				lfree = rand() % SIZE;
			} while (!addr[lfree]);
			tiny_free(addr[lfree]);
			addr[lfree] = NULL;
		}
		i++;
	}

	iterate_block_list(mem_start);

	for (i = 0; i < SIZE; i++)
		tiny_free(addr[i]);

	iterate_block_list(mem_start);

	free(mem_start);
	return 0;
}
