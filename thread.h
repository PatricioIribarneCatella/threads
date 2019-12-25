#ifndef THREAD_H
#define THREAD_H

#include <stddef.h>
#include <sys/types.h>

typedef pid_t thread_t;

thread_t thread_create(int (*fn)(void*), void* arg);
thread_t thread_wait(thread_t t);

#endif // THREAD_H