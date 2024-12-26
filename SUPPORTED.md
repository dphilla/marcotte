# Supported libc functions, POSIX-conformance (meaning, interfaces, majority of behavior)

Which libc is this? TL;DR: it's a combo of mostly musl, some glibc, and other creative additions for compat.[Read more on this](boxer.dev/blog)

[Musl test suite](https://git.musl-libc.org/cgit/libc-testsuite/tree/README), for reference, E2E testing, and for future cross-compat, the [glibc test suite](https://sourceware.org/glibc/wiki/Testing/Testsuite).

## Networking (~65 funcs)

| Function              | Supported | Source                                   | Notes |
|-----------------------|-----------|------------------------------------------|-------|
| `socket()`            | ✅         | [header](sys/socket.h)/[src](src/network/socket.c) |       |
| `bind()`              |           |                                          |       |
| `connect()`           |           |                                          |       |
| `listen()`            |           |                                          |       |
| `accept()`            |           |                                          |       |
| `accept4()`           |           |                                          |       |
| `recv()`              |           |                                          |       |
| `send()`              |           |                                          |       |
| `recvfrom()`          |           |                                          |       |
| `sendto()`            |           |                                          |       |
| `recvmsg()`           |           |                                          |       |
| `sendmsg()`           |           |                                          |       |
| `getaddrinfo()`       |           |                                          |       |
| `freeaddrinfo()`      |           |                                          |       |
| `getnameinfo()`       |           |                                          |       |
| `poll()`              |           |                                          |       |
| `select()`            |           |                                          |       |
| `shutdown()`          |           |                                          |       |
| `setsockopt()`        |           |                                          |       |
| `getsockopt()`        |           |                                          |       |
| `inet_aton()`         |           |                                          |       |
| `inet_ntoa()`         |           |                                          |       |
| `inet_pton()`         |           |                                          |       |
| `inet_ntop()`         |           |                                          |       |
| `gethostname()`       |           |                                          |       |
| `gethostbyname()`     |           |                                          | Deprecated, use `getaddrinfo()` instead |
| `gethostbyaddr()`     |           |                                          | Deprecated, use `getaddrinfo()` instead |
| `socketpair()`        |           |                                          |       |
| `ioctl()`             |           |                                          | Often used for socket control            |
| `fcntl()`             |           |                                          |       |
| `epoll_create()`      |           |                                          | Linux-specific |
| `epoll_create1()`     |           |                                          | Linux-specific |
| `epoll_ctl()`         |           |                                          | Linux-specific |
| `epoll_wait()`        |           |                                          | Linux-specific |
| `eventfd()`           |           |                                          | Linux-specific |
| `getpeername()`       |           |                                          |       |
| `getsockname()`       |           |                                          |       |
| `sendfile()`          |           |                                          |       |
| `readv()`             |           |                                          |       |
| `writev()`            |           |                                          |       |
| `splice()`            |           |                                          |       |
| `tee()`               |           |                                          | Linux-specific |
| `vmsplice()`          |           |                                          | Linux-specific |
| `getifaddrs()`        |           |                                          | Requires `<ifaddrs.h>` |
| `freeifaddrs()`       |           |                                          | Requires `<ifaddrs.h>` |
| `if_nametoindex()`    |           |                                          | Requires `<net/if.h>` |
| `if_indextoname()`    |           |                                          | Requires `<net/if.h>` |
| `if_nameindex()`      |           |                                          | Requires `<net/if.h>` |
| `if_freenameindex()`  |           |                                          | Requires `<net/if.h>` |
| `pselect()`           |           |                                          |       |
| `epoll_pwait()`       |           |                                          | Linux-specific |
| `sendmmsg()`          |           |                                          | Linux-specific |
| `recvmmsg()`          |           |                                          | Linux-specific |
| `getprotobyname()`    |           |                                          |       |
| `getprotobynumber()`  |           |                                          |       |
| `getservbyname()`     |           |                                          |       |
| `getservbyport()`     |           |                                          |       |
| `hstrerror()`         |           |                                          | Obsolete for modern use |
| `inet_makeaddr()`     |           |                                          |       |
| `inet_lnaof()`        |           |                                          |       |
| `inet_netof()`        |           |                                          |       |
| `inet_network()`      |           |                                          |       |


## Filesystem (~140 funcs)

| **Function**      | **Supported** | **Header/Src**                       | **Notes**                                                                           |
|-------------------|---------------|---------------------------------------|-------------------------------------------------------------------------------------|
| **fopen**         | Yes           | `<stdio.h>` / `src/stdio/fopen.c`     | Backed by `wasm_vfs_open`.                                                          |
| **fclose**        | Yes           | `<stdio.h>` / `src/stdio/fclose.c`    | Frees `FILE*`, calls `wasm_vfs_close`.                                              |
| **freopen**       | Yes           | `<stdio.h>` / `src/stdio/freopen.c`   | Closes old, re-opens.                                                               |
| **fflush**        | Partial       | `<stdio.h>` / `src/stdio/fflush.c`    | No-op (unbuffered).                                                                 |
| **fgetc**         | Yes           | `<stdio.h>` / `src/stdio/fgetc.c`     | Reads 1 byte with `wasm_vfs_read`.                                                  |
| **fgets**         | Yes           | `<stdio.h>` / `src/stdio/fgets.c`     | Reads linewise.                                                                     |
| **fputc**         | Yes           | `<stdio.h>` / `src/stdio/fputc.c`     | Writes single byte.                                                                 |
| **fputs**         | Yes           | `<stdio.h>` / `src/stdio/fputs.c`     | Writes string.                                                                      |
| **fread**         | Yes           | `<stdio.h>` / `src/stdio/fread.c`     | Wraps `wasm_vfs_read`.                                                              |
| **fwrite**        | Yes           | `<stdio.h>` / `src/stdio/fwrite.c`    | Wraps `wasm_vfs_write`.                                                             |
| **fseek**         | Yes           | `<stdio.h>` / `src/stdio/fseek.c`     | Uses `wasm_vfs_lseek`.                                                              |
| **ftell**         | Yes           | `<stdio.h>` / `src/stdio/ftell.c`     | Uses `lseek(fd,0,SEEK_CUR)`.                                                        |
| **rewind**        | Yes           | `<stdio.h>` / `src/stdio/rewind.c`    | `fseek(..., 0, SEEK_SET)`.                                                          |
| **fgetpos**       | Yes           | `<stdio.h>` / `src/stdio/fgetpos.c`   | Wraps `ftell`.                                                                      |
| **fsetpos**       | Yes           | `<stdio.h>` / `src/stdio/fsetpos.c`   | Wraps `fseek`.                                                                      |
| **clearerr**      | Yes           | `<stdio.h>` / `src/stdio/clearerr.c`  | Clears `eof`/`error`.                                                               |
| **feof**          | Yes           | `<stdio.h>` / `src/stdio/feof.c`      | Returns `FILE->eof`.                                                                |
| **ferror**        | Yes           | `<stdio.h>` / `src/stdio/ferror.c`    | Returns `FILE->error`.                                                              |
| **perror**        | Partial       | `<stdio.h>` / `src/stdio/perror.c`    | Prints a simple message (no real errno).                                            |
| **tmpfile**       | Yes           | `<stdio.h>` / `src/stdio/tmpfile.c`   | Creates ephemeral file in `/tmp`.                                                   |
| **tmpfile64**     | Yes           | `<stdio.h>` / `src/stdio/tmpfile64.c` | Same as `tmpfile`.                                                                  |
| **tempnam**       | Partial       | `<stdio.h>` / `src/stdio/tempnam.c`   | Just returns a random string in `/tmp`.                                             |
| **setbuf**        | Partial       | `<stdio.h>` / `src/stdio/setbuf.c`    | No-op for buffering.                                                                |
| **setvbuf**       | Partial       | `<stdio.h>` / `src/stdio/setvbuf.c`   | No-op for buffering.                                                                |
| **ungetc**        | Partial       | `<stdio.h>` / `src/stdio/ungetc.c`    | Stub (no real pushback buffer).                                                     |
| **fileno**        | Yes           | `<stdio.h>` / `src/stdio/fileno.c`    | Returns `FILE->fd`.                                                                 |
| **popen**         | Stub          | `<stdio.h>` / `src/stdio/popen.c`     | Not feasible in pure wasm env.                                                      |
| **pclose**        | Stub          | `<stdio.h>` / `src/stdio/pclose.c`    | Stub.                                                                               |
| **access**        | Yes           | `<unistd.h>` / `src/unistd/access.c`  | Calls `wasm_vfs_access`.                                                            |
| **chmod**         | Yes           | `<sys/stat.h>` / `src/sys/stat/chmod.c`   | `wasm_vfs_chmod`.                                                              |
| **chown**         | Yes           | `<unistd.h>` / `src/unistd/chown.c`   | `wasm_vfs_chown`.                                                                   |
| **close**         | Yes           | `<unistd.h>` / `src/unistd/close.c`   | `wasm_vfs_close`.                                                                   |
| **creat**         | Yes           | `<fcntl.h>` / `src/fcntl/creat.c`     | `open(..., O_WRONLY|O_CREAT|O_TRUNC)`.                                             |
| **dup**           | Yes           | `<unistd.h>` / `src/unistd/dup.c`      | `wasm_vfs_dup`.                                                                     |
| **dup2**          | Yes           | `<unistd.h>` / `src/unistd/dup2.c`     | `wasm_vfs_dup2`.                                                                    |
| **dup3**          | Partial       | `<unistd.h>` / `src/unistd/dup3.c`     | Ignores extra flags, calls `dup2`.                                                  |
| **fchmod**        | Yes           | `<sys/stat.h>` / `src/sys/stat/fchmod.c` | `wasm_vfs_fchmod`.                                                              |
| **fchown**        | Yes           | `<unistd.h>` / `src/unistd/fchown.c`  | `wasm_vfs_fchown`.                                                                  |
| **fcntl**         | Partial       | `<fcntl.h>` / `src/fcntl/fcntl.c`     | Not shown above; typically stubs for lock, etc.                                     |
| **fdatasync**     | Stub          | `<unistd.h>` / `src/unistd/fdatasync.c` | No-op.                                                                           |
| **flock**         | Stub          | `<sys/file.h>` / `src/sys/file/flock.c` | No-op.                                                                           |
| **fsync**         | Stub          | `<unistd.h>` / `src/unistd/fsync.c`   | No-op.                                                                              |
| **ftruncate**     | Yes           | `<unistd.h>` / `src/unistd/ftruncate.c` | `wasm_vfs_ftruncate`.                                                            |
| **lseek**         | Yes           | `<unistd.h>` / `src/unistd/lseek.c`    | `wasm_vfs_lseek`.                                                                  |
| **mmap**          | Stub          | `<sys/mman.h>` / `src/sys/mman/mmap.c` | Returns `MAP_FAILED`; not feasible.                                                |
| **munmap**        | Stub          | `<sys/mman.h>` / `src/sys/mman/munmap.c` | No-op, returns -1.                                                               |
| **pread**         | Yes           | `<unistd.h>` / `src/unistd/pread.c`    | `wasm_vfs_pread64`.                                                                |
| **pwrite**        | Yes           | `<unistd.h>` / `src/unistd/pwrite.c`   | `wasm_vfs_pwrite64`.                                                               |
| **read**          | Yes           | `<unistd.h>` / `src/unistd/read.c`     | `wasm_vfs_read`.                                                                   |
| **write**         | Yes           | `<unistd.h>` / `src/unistd/write.c`    | `wasm_vfs_write`.                                                                  |
| **unlink**        | Yes           | `<unistd.h>` / `src/unistd/unlink.c`   | `wasm_vfs_unlink`.                                                                 |
| **fstat**         | Yes           | `<sys/stat.h>` / `src/sys/stat/fstat.c`| `wasm_vfs_fstat`.                                                                  |
| **fstatat**       | Yes           | `<sys/stat.h>` / `src/sys/stat/fstatat.c`| `wasm_vfs_fstatat`.                                                             |
| **stat**          | Yes           | `<sys/stat.h>` / `src/sys/stat/stat.c` | `wasm_vfs_stat`.                                                                   |
| **lstat**         | Yes           | `<sys/stat.h>` / `src/sys/stat/lstat.c`| `wasm_vfs_lstat`.                                                                  |
| **utime**         | Partial       | `<utime.h>` / `src/utime/utime.c`      | Could set `inode.mtime`, not shown in code.                                        |
| **opendir**       | Yes           | `<dirent.h>` / `src/dirent/opendir.c`  | opens a dir FD with `open()`.                                                      |
| **readdir**       | Yes           | `<dirent.h>` / `src/dirent/readdir.c`  | uses `wasm_vfs_getdents`.                                                          |
| **readdir_r**     | Partial       | `<dirent.h>` / `src/dirent/readdir_r.c`| Typically replaced by `readdir` in modern code.                                    |
| **rewinddir**     | Yes           | `<dirent.h>` / `src/dirent/rewinddir.c`| calls `lseek(dirfd, 0, SEEK_SET)`.                                                 |
| **closedir**      | Yes           | `<dirent.h>` / `src/dirent/closedir.c` | closes the FD, frees struct.                                                       |
| **mkdir**         | Yes           | `<sys/stat.h>` / `src/sys/stat/mkdir.c`| `wasm_vfs_mkdir`.                                                                  |
| **rmdir**         | Yes           | `<unistd.h>` / `src/unistd/rmdir.c`    | `wasm_vfs_rmdir`.                                                                  |
| **chdir**         | Yes           | `<unistd.h>` / `src/unistd/chdir.c`    | `wasm_vfs_chdir`.                                                                  |
| **fchdir**        | Yes           | `<unistd.h>` / `src/unistd/fchdir.c`   | `wasm_vfs_fchdir`.                                                                 |
| **getcwd**        | Yes           | `<unistd.h>` / `src/unistd/getcwd.c`   | `wasm_vfs_getcwd`.                                                                 |
| **truncate**      | Yes           | `<unistd.h>` / `src/unistd/truncate.c` | `wasm_vfs_truncate`.                                                               |
| **mount**         | Stub          | `<sys/mount.h>` / `src/sys/mount/mount.c`  | Not feasible in wasm.                                                         |
| **umount**        | Stub          | `<sys/mount.h>` / `src/sys/mount/umount.c` | Not feasible.                                                                 |
| **umount2**       | Stub          | `<sys/mount.h>` / `src/sys/mount/umount2.c`| Not feasible.                                                                 |
| **readlink**      | Yes           | `<unistd.h>` / `src/unistd/readlink.c` | `wasm_vfs_readlink`.                                                               |
| **pipe**          | Stub          | `<unistd.h>` / `src/unistd/pipe.c`     | Not implemented.                                                                   |
| **pipe2**         | Stub          | `<unistd.h>` / `src/unistd/pipe2.c`    | Same reason.                                                                       |
| **symlink**       | Yes           | `<unistd.h>` / `src/unistd/symlink.c`  | `wasm_vfs_symlink`.                                                                |
| **link**          | Yes           | `<unistd.h>` / `src/unistd/link.c`     | `wasm_vfs_link`.                                                                   |
| **rename**        | Yes           | `<unistd.h>` / `src/unistd/rename.c`   | `wasm_vfs_rename`.                                                                 |
| **renameat**      | Yes           | `<unistd.h>` / `src/unistd/renameat.c` | calls `wasm_vfs_rename`.                                                           |
| **renameat2**     | Partial       | `<unistd.h>` / `src/unistd/renameat2.c`| same as renameat, ignoring flags.                                                  |
| **sync**          | Stub          | `<unistd.h>` / `src/unistd/sync.c`     | no-op.                                                                              |
| **syncfs**        | Stub          | `<unistd.h>` / `src/unistd/syncfs.c`   | no-op.                                                                              |
| **tee**           | Stub          | `<unistd.h>` / `src/unistd/tee.c`      | Not implemented.                                                                    |
| **splice**        | Yes           | `<unistd.h>` / `src/unistd/splice.c`   | calls `wasm_vfs_splice`.                                                            |
| **vmsplice**      | Stub          | `<unistd.h>` / `src/unistd/vmsplice.c` | Not implemented.                                                                    |
| **sendfile**      | Yes           | `<unistd.h>` / `src/unistd/sendfile.c` | calls `wasm_vfs_sendfile`.                                                          |
| **faccessat**     | Yes           | `<unistd.h>` / `src/unistd/faccessat.c`| calls `wasm_vfs_faccessat`.                                                         |
| **openat**        | Yes           | `<fcntl.h>` / `src/fcntl/openat.c`     | calls `wasm_vfs_openat`.                                                            |
| **mkfifo**        | Stub          | `<sys/stat.h>` / `src/sys/stat/mkfifo.c`   | Not implemented.                                                                |
| **mkfifoat**      | Stub          | `<sys/stat.h>` / `src/sys/stat/mkfifoat.c` | Not implemented.                                                                |
| **mknod**         | Stub          | `<sys/stat.h>` / `src/sys/stat/mknod.c`    | Not implemented.                                                                |
| **mknodat**       | Stub          | `<sys/stat.h>` / `src/sys/stat/mknodat.c`  | Not implemented.                                                                |
| **chroot**        | Stub          | `<unistd.h>` / `src/unistd/chroot.c`?      | Typically privileged op, not implemented.                                       |
| **fchmodat**      | Yes           | `<sys/stat.h>` / `src/sys/stat/fchmodat.c` | calls `chmod()`.                                                               |
| **fchownat**      | Yes           | `<unistd.h>` / `src/unistd/fchownat.c`     | calls `chown()`.                                                               |
| **lchown**        | Yes           | `<unistd.h>` / `src/unistd/lchown.c`       | same as `chown`.                                                               |
| **mkstemp**       | Partial       | `<unistd.h>` / `src/unistd/mkstemp.c`      | You can create a file from template. Not shown, but trivial to do.             |
| **mkstemps**      | Partial       | `<unistd.h>` / `src/unistd/mkstemps.c`     | Variation of mkstemp.                                                          |
| **mktemp**        | Partial       | `<stdio.h>` / `src/stdio/mktemp.c`        | We replace XXXXXX with random.                                                 |
| **tmpnam**        | Partial       | `<stdio.h>` / `src/stdio/tmpnam.c`        | Provides a unique path in /tmp.                                                |
| **getxattr** etc. | Stub          | `<sys/xattr.h>` / not shown              | Extended attributes not implemented.                                            |
| **preadv**, **pwritev** | Stub or partial | `<sys/uio.h>` / not shown | Could be done similarly to `pread`/`pwrite`.                                    |
| **copy_file_range** | Stub        | `<unistd.h>` / not shown                | Not implemented.                                                                |
| **linkat2**       | Stub          | Not standard POSIX, ignoring.           | -                                                                                |


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

