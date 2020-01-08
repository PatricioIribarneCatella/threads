#define _GNU_SOURCE

#include <sched.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "thread.h"

#define MEM_SIZE (1 << 13) // 8 Kb = 2 pages
#define STACK_SIZE (1 << 12) // 4 Kb

thread_t thread_create(int (*fn)(void*), void* arg) {

	char *mem;
	thread_t id;

	// Two pages of memory are reserved for the thread (8 kb).
	// This is because in the case that the thread uses more than one page,
	// it will fault instead of generating a "Segmentation Fault".
	// Then, the OS will only need to change the permissions on the
	// following page ("Guard Pages").
	//
	mem = mmap(NULL, MEM_SIZE,
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS,
			-1, 0);

	mprotect(mem, STACK_SIZE, PROT_NONE);
	
	id = clone(fn, mem + MEM_SIZE - 1, CLONE_VM | SIGCHLD, arg);

	return id;
}

thread_t thread_wait(thread_t t) {

	return waitpid(t, NULL, 0);
}

