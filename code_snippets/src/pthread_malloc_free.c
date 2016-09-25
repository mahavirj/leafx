#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define MAX_SIZE 32

typedef struct queue_t {
	void *arr[MAX_SIZE];
	int rd;
	int wr;
} queue_t;

static pthread_mutex_t lock_x;
static pthread_cond_t count_consumer, count_producer;
static queue_t q;

int enqueue(void *addr)
{
	if (!addr)
		return -1;
	if (((q.wr + 1) % MAX_SIZE) == q.rd)
		return -1;

	q.arr[q.wr] = addr;
	q.wr = (q.wr + 1) % MAX_SIZE;
	return 0;
}

int dequeue(unsigned long *addr)
{
	if (q.rd == q.wr)
		return -1;

	*addr = (unsigned long) q.arr[q.rd];
	q.rd = (q.rd + 1) % MAX_SIZE;
	return 0;
}

void *thr_func_1(void *arg)
{
	printf("Producer thread\n");
	void *addr;

	do {
		addr = malloc(1024);
		if (!addr)
			break;
		printf("Alloc at %p\n", addr);
		pthread_mutex_lock(&lock_x);
		while (enqueue(addr) != 0) {
			pthread_cond_wait(&count_producer, &lock_x);			
		}
		pthread_cond_signal(&count_consumer);
		pthread_mutex_unlock(&lock_x);
	} while (1);

	pthread_exit(NULL);
}

void *thr_func_2(void *arg)
{
	printf("Consumer thread\n");
	unsigned long addr;
	
	do {
		pthread_mutex_lock(&lock_x);
		while (dequeue(&addr) != 0) {
			pthread_cond_wait(&count_consumer, &lock_x);
		}
		pthread_cond_signal(&count_producer);
		pthread_mutex_unlock(&lock_x);
		printf("Free at %p\n", (void *) addr);
		free((void *) addr);
	} while (1);

	pthread_exit(NULL);
}

int main(void)
{
	pthread_t thr[NUM_THREADS];
	int i, rc;
	/* initialize pthread mutex protecting "shared_x" */
	pthread_mutex_init(&lock_x, NULL);
	pthread_cond_init(&count_consumer, NULL);
	pthread_cond_init(&count_producer, NULL);

	/* create threads */
	if ((rc = pthread_create(&thr[0], NULL, thr_func_1, NULL))) {
		fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
		return EXIT_FAILURE;
	}
	if ((rc = pthread_create(&thr[1], NULL, thr_func_2, NULL))) {
		fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
		return EXIT_FAILURE;
	}
	/* block until all threads complete */
	for (i = 0; i < NUM_THREADS; ++i) {
		pthread_join(thr[i], NULL);
	}
	pthread_mutex_destroy(&lock_x);
	pthread_cond_destroy(&count_consumer);
	pthread_cond_destroy(&count_producer);
	return EXIT_SUCCESS;
}
