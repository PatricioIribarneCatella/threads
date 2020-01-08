CFLAGS := -std=c99 -g
CC := gcc
BIN := $(filter-out main.c main-thread.c, $(wildcard *.c))
BINFILES := $(BIN:.c=.o)

all: spin spin-thread

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

spin-thread: $(BINFILES) main-thread.c
	$(CC) $(CFLAGS) $^ -o $@
	objdump -S $@ > $@.asm

spin: $(BINFILES) main.c
	$(CC) $(CFLAGS) $^ -o $@
	objdump -S $@ > $@.asm

clean:
	rm -f spin spin-thread *.o *.asm

time: spin
	/usr/bin/time -f "R: %e\nU: %U\nS: %S\nC: %w/%c\n" ./$<

time-thread: spin-thread
	/usr/bin/time -f "R: %e\nU: %U\nS: %S\nC: %w/%c\n" ./$<

valgrind: spin
	valgrind ./$<

valgrind_thread: spin-thread
	valgrind ./$<

strace: spin
	strace ./$<

.PHONY: clean time strace valgrind valgrind-thread
