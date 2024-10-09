# Supported libc functions, POSIX-conformance

Which libc is this? TL;DR: it's a combo of mostly musl, some glibc, and other creative additions for compat.[Read more on this](boxer.dev/blog)

## Filesystem

| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `fopen()`             |           |              |       |                          |
| `fclose()`            |           |              |       |                          |
| `open()`              |           |              |       |                          |
| `close()`             |           |              |       |                          |
| `opendir()`           |           |              |       |                          |
| `readdir()`           |           |              |       |                          |
| `stat()`              |           |              |       |                          |
| `chmod()`             |           |              |       |                          |
| `unlink()`            |           |              |       |                          |
| `rename()`            |           |              |       |                          |
|                       |           |              |       |                          |

## Networking

| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `socket()`            |           |              |       |                          |
| `bind()`              |           |              |       |                          |
| `connect()`           |           |              |       |                          |
| `listen()`            |           |              |       |                          |
| `recv()`              |           |              |       |                          |
| `send()`              |           |              |       |                          |
| `getaddrinfo()`       |           |              |       |                          |
| `freeaddrinfo()`      |           |              |       |                          |
| `poll()`              |           |              |       |                          |
| `select()`            |           |              |       |                          |
|                       |           |              |       |                          |

## Self-Contained (requires no kernel interactions.. mostly)
| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `sin()`               |           |              |       |                          |
| `cos()`               |           |              |       |                          |
| `tan()`               |           |              |       |                          |
| `memcpy()`            |           |              |       |                          |
| `memset()`            |           |              |       |                          |
| `strcmp()`            |           |              |       |                          |
| `strlen()`            |           |              |       |                          |
| `isalpha()`           |           |              |       |                          |
| `isdigit()`           |           |              |       |                          |
| `qsort()`             |           |              |       |                          |
| `bsearch()`           |           |              |       |                          |
|                       |           |              |       |                          |

## Process and Thread Management

| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `fork()`              |           |              |       |                          |
| `execve()`            |           |              |       |                          |
| `pthread_create()`    |           |              |       |                          |
| `pthread_mutex_lock()`|           |              |       |                          |
| `wait()`              |           |              |       |                          |
| `waitpid()`           |           |              |       |                          |
|                       |           |              |       |                          |

## Signals

| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `signal()`            |           |              |       |                          |
| `sigaction()`         |           |              |       |                          |
| `kill()`              |           |              |       |                          |
| `raise()`             |           |              |       |                          |
| `sigprocmask()`       |           |              |       |                          |
|                       |           |              |       |                          |

## Time and Date

| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `time()`              |           |              |       |                          |
| `gettimeofday()`      |           |              |       |                          |
| `clock_gettime()`     |           |              |       |                          |
| `nanosleep()`         |           |              |       |                          |
|                       |           |              |       |                          |

## Memory Management

| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `mmap()`              |           |              |       |                          |
| `munmap()`            |           |              |       |                          |
| `mprotect()`          |           |              |       |                          |
| `brk()`               |           |              |       |                          |
|                       |           |              |       |                          |

## Environment and User Information

| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `getenv()`            |           |              |       |                          |
| `setenv()`            |           |              |       |                          |
| `getuid()`            |           |              |       |                          |
| `getgid()`            |           |              |       |                          |
| `getlogin()`          |           |              |       |                          |
|                       |           |              |       |                          |

## Locale and Internationalization

| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `setlocale()`         |           |              |       |                          |
| `wctomb()`            |           |              |       |                          |
| `mbtowc()`            |           |              |       |                          |
| `localeconv()`        |           |              |       |                          |
|                       |           |              |       |                          |





