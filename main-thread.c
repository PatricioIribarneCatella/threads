#include <stdio.h>

#include "thread.h"

#define IDSIZE 32
#define SIZE 100000000

static char vec[SIZE];

typedef struct {
	char *data;
	char id[IDSIZE];
} arg_t;

static int work(void *arg) {

	arg_t *c = (arg_t *) arg;

	for (int i = 0; i < SIZE; i++)
		c->data[i]++;

	printf("thread: %s end\n", c->id);

	return 0;
}

int main(void) {

	thread_t t1, t2;
	arg_t a = {vec, "A"}, b = {vec, "B"};

	t1 = thread_create(work, &a);
	t2 = thread_create(work, &b);

	thread_wait(t1);
	thread_wait(t2);

	printf("main done\n");

	return 0;
}

