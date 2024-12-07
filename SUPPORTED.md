# Supported libc functions, POSIX-conformance (meaning, interfaces, majority of behavior)

Which libc is this? TL;DR: it's a combo of mostly musl, some glibc, and other creative additions for compat.[Read more on this](boxer.dev/blog)

[Musl test suite](https://git.musl-libc.org/cgit/libc-testsuite/tree/README), for reference, E2E testing, and for future cross-compat, the [glibc test suite](https://sourceware.org/glibc/wiki/Testing/Testsuite).

## Networking (~65 funcs)

| Function              | Supported | Source       | Notes |
|-----------------------|-----------|--------------|-------|
| `socket()`            |✅         |[header](sys/socket.h)/[src](src/network/socket.c) |       |
| `bind()`              |           |              |       |
| `connect()`           |           |              |       |
| `listen()`            |           |              |       |
| `recv()`              |           |              |       |
| `send()`              |           |              |       |
| `getaddrinfo()`       |           |              |       |
| `freeaddrinfo()`      |           |              |       |
| `poll()`              |           |              |       |
| `select()`            |           |              |       |
|                       |           |              |       |

## Filesystem (~140 funcs)

| Function              | Supported | Header/Src   | Notes |
|-----------------------|-----------|--------------|-------|
|fopen             |           |  |       |
|fclose  |           |              |       |
|freopen  |           |              |       |
|fflush  |           |              |       |
|fgetc  |           |              |       |
|fgets  |           |              |       |
|fputc  |           |              |       |
|fputs  |           |              |       |
|fread  |           |              |       |
|fwrite  |           |              |       |
|fseek  |           |              |       |
|ftell  |           |              |       |
|rewind  |           |              |       |
|fgetpos  |           |              |       |
|fsetpos  |           |              |       |
|clearerr  |           |              |       |
|feof  |           |              |       |
|ferror  |           |              |       |
|perror  |           |              |       |
|tmpfile  |           |              |       |
|tmpfile64  |           |              |       |
|tempnam  |           |              |       |
|setbuf  |           |              |       |
|setvbuf  |           |              |       |
|ungetc  |           |              |       |
|fileno  |           |              |       |
|popen  |           |              |       |
|pclose  |           |              |       |
|access  |           |              |       |
|chmod|           |              |       |
|chown|           |              |       |
|close|           |              |       |
|creat|           |              |       |
|dup|           |              |       |
|dup2|           |              |       |
|dup3|           |              |       |
|fchmod|           |              |       |
|fchown|           |              |       |
|fcntl|           |              |       |
|fdatasync|           |              |       |
|flock|           |              |       |
|fsync|           |              |       |
|ftruncate|           |              |       |
|lseek|           |              |       |
|mmap|           |              |       |
|munmap|           |              |       |
|pread|           |              |       |
|pwrite|           |              |       |
|read|           |              |       |
|readv|           |              |       |
|write|           |              |       |
|writev|           |              |       |
|unlink|           |              |       |
|fstat|           |              |       |
|fstatat|           |              |       |
|stat|           |              |       |
|lstat|           |              |       |
|utime|           |              |       |
|utimes|           |              |       |
|futimes|           |              |       |
|futimens|           |              |       |
|faccessat|           |              |       |
|opendir|           |              |       |
|readdir|           |              |       |
|readdir_r|           |              |       |
|rewinddir|           |              |       |
|closedir|           |              |       |
|seekdir|           |              |       |
|telldir|           |              |       |
|open|           |              |       |
|openat|           |              |       |
|mkfifo|           |              |       |
|mkfifoat|           |              |       |
|mknod|           |              |       |
|mknodat|           |              |       |
|rename|           |              |       |
|renameat|           |              |       |
|symlink|           |              |       |
|symlinkat|           |              |       |
|link|           |              |       |
|linkat|           |              |       |
|readlink|           |              |       |
|readlinkat|           |              |       |
|dup|           |              |       |
|dup2|           |              |       |
|dup3|           |              |       |
|pipe|           |              |       |
|pipe2|           |              |       |
|mkdir|           |              |       |
|mkdirat|           |              |       |
|rmdir|           |              |       |
|chdir|           |              |       |
|fchdir|           |              |       |
|getcwd|           |              |       |
|statfs|           |              |       |
|fstatfs|           |              |       |
|statvfs|           |              |       |
|fstatvfs|           |              |       |
|pathconf|           |              |       |
|fpathconf|           |              |       |
|truncate|           |              |       |
|ftruncate|           |              |       |
|mount|           |              |       |
|umount|           |              |       |
|umount2|           |              |       |
|symlink|           |              |       |
|symlinkat|           |              |       |
|readlink|           |              |       |
|readlinkat|           |              |       |
|chroot|           |              |       |
|realpath|           |              |       |
|chmod|           |              |       |
|fchmod|           |              |       |
|fchmodat|           |              |       |
|chown|           |              |       |
|fchown|           |              |       |
|fchownat|           |              |       |
|lchown|           |              |       |
|mkstemp|           |              |       |
|mkstemps|           |              |       |
|mktemp|           |              |       |
|tmpfile|           |              |       |
|tmpnam|           |              |       |
|getxattr|           |              |       |
|fgetxattr|           |              |       |
|setxattr|           |              |       |
|fsetxattr|           |              |       |
|listxattr|           |              |       |
|flistxattr|           |              |       |
|removexattr|           |              |       |
|fremovexattr|           |              |       |
|preadv|           |              |       |
|pwritev|           |              |       |
|sendfile|           |              |       |
|sync|           |              |       |
|syncfs|           |              |       |
|tee|           |              |       |
|splice|           |              |       |
|vmsplice|           |              |       |
|renameat2|           |              |       |
|copy_file_range|           |              |       |
|linkat2|           |              |       |



## Self-Contained (requires no kernel interactions.. mostly, ~400 functions)
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

## Process and Thread Management (~70 func)

| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `fork()`              |           |              |       |                          |
| `execve()`            |           |              |       |                          |
| `pthread_create()`    |           |              |       |                          |
| `pthread_mutex_lock()`|           |              |       |                          |
| `wait()`              |           |              |       |                          |
| `waitpid()`           |           |              |       |                          |
|                       |           |              |       |                          |

## Signals (~20)

| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `signal()`            |           |              |       |                          |
| `sigaction()`         |           |              |       |                          |
| `kill()`              |           |              |       |                          |
| `raise()`             |           |              |       |                          |
| `sigprocmask()`       |           |              |       |                          |
|                       |           |              |       |                          |

## Time and Date (~25 funcs)

| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `time()`              |           |              |       |                          |
| `gettimeofday()`      |           |              |       |                          |
| `clock_gettime()`     |           |              |       |                          |
| `nanosleep()`         |           |              |       |                          |
|                       |           |              |       |                          |

## Memory Management (~10 funcs)

| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `mmap()`              |           |              |       |                          |
| `munmap()`            |           |              |       |                          |
| `mprotect()`          |           |              |       |                          |
| `brk()`               |           |              |       |                          |
|                       |           |              |       |                          |

## Environment and User Information (~15 funcs)

| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `getenv()`            |           |              |       |                          |
| `setenv()`            |           |              |       |                          |
| `getuid()`            |           |              |       |                          |
| `getgid()`            |           |              |       |                          |
| `getlogin()`          |           |              |       |                          |
|                       |           |              |       |                          |

## Locale and Internationalization (~15 funcs)

| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `setlocale()`         |           |              |       |                          |
| `wctomb()`            |           |              |       |                          |
| `mbtowc()`            |           |              |       |                          |
| `localeconv()`        |           |              |       |                          |
|                       |           |              |       |                          |

## Standard I/O and Formatting (~40 funcs)
| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `printf()`     | | | ||
| `sprintf()`    | | | ||
| `scanf()`       | | | ||
| `sscanf()`      | | | ||


## Dynamic Linking and Loading (~10 funcs)
| Function              | Supported | Source       | Notes | Original Reference       |
|-----------------------|-----------|--------------|-------|--------------------------|
| `dlopen()`    | | | ||
| `dlsym()`    | | | ||
| `dlclose()`     | | | ||

