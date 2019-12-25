#define _GNU_SOURCE

#include <stdlib.h>
#include <sched.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "thread.h"

#define MEM_SIZE (1 << 13) // 8 Kb = 2 pages
#define STACK_SIZE (1 << 12) // 4 Kb

thread_t thread_create(int (*fn)(void*), void* arg) {

	/* Se reservan dos páginas para el stack. Luego con mprotect() se cambian los permisos de la última página del stack
	 * para que sea no accesible pero seguir estando mapeada.
	
	 * Si la función necesitara más stack del provisto (1 página) se producirá una PageFault
	 * en vez de una Segmentation Fault y el SO tendrá que solo cambiar los permisos y no mapear
	 * una nueva página en ese momento. ("Guard Pages")
	*/
	char* m = mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	mprotect(m, STACK_SIZE, PROT_NONE);
	
	return clone(fn, m + MEM_SIZE - 1, CLONE_VM | SIGCHLD, arg);
}

thread_t thread_wait(thread_t t) {

	return waitpid(t, NULL, 0);
}

