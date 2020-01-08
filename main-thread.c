#include <stdio.h>

#include "thread.h"

#define SIZE 100000000

static char a[SIZE];
static char b[SIZE];

static int work(void* arg) {

	char* c = (char*)arg;

	for (int i = 0; i < SIZE; i++)
		c[i]++;

	printf("thread end\n");

	return 0;
}

int main(void) {

	thread_t t1, t2;

	t1 = thread_create(work, a);
	t2 = thread_create(work, b);

	thread_wait(t1);
	thread_wait(t2);

	printf("main done\n");

	return 0;
}
