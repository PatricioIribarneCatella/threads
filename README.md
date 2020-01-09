# threads

Very simple and brief _Threads API_ implementation with `clone(2)`

### Dependencies

- [Valgrind](https://valgrind.org/)
- [Strace](https://linux.die.net/man/1/strace)

### Compile

```bash
$ make
```

### Run

#### With _Threads_

- Time measurement

```bash
$ make time-thread
```

- Valgrind

```bash
$ make valgrind-thread
```

- _Strace_

```bash
$ make strace-thread
```

#### Without _Threads_

- Time measurement

```bash
$ make time
```

- Valgrind

```bash
$ make valgrind
```

- _Strace_

```bash
$ make strace
```

