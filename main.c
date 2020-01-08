#include <stdio.h>

#define SIZE 100000000

static char a[SIZE];

static int work(void* arg) {

	char* c = (char*)arg;

	for (int i = 0; i < SIZE; i++)
		c[i]++;

	printf("array end\n");

	return 0;
}

int main(void) {

	work(a);
	work(a);

	printf("main done\n");

	return 0;
}
