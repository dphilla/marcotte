# Supported libc functions, POSIX-conformance (meaning, interfaces, majority of behavior)

Which libc is this? TL;DR: it's a combo of mostly musl, some glibc, and other creative additions for compat.[Read more on this](boxer.dev/blog)

[Musl test suite](https://git.musl-libc.org/cgit/libc-testsuite/tree/README), for reference, E2E testing, and for future cross-compat, the [glibc test suite](https://sourceware.org/glibc/wiki/Testing/Testsuite).

## Networking (~65 funcs)

| Function              | Supported | Source                                                | Notes                                                       |
|-----------------------|-----------|-------------------------------------------------------|-------------------------------------------------------------|
| `socket()`            | Yes       | [header](sys/socket.h) / [src](src/network/socket.c) | Standard done previously                                    |
| `bind()`              | Yes       | [src](src/network/bind.c)                             |                                                             |
| `connect()`           | Yes       | [src](src/network/connect.c)                          |                                                             |
| `listen()`            | Yes       | [src](src/network/listen.c)                           |                                                             |
| `accept()`            | Yes       | [src](src/network/accept.c)                           | Complex pointer out for addr                                |
| `accept4()`           | Yes       | [src](src/network/accept4.c)                          | Same pattern as accept + flags                              |
| `recv()`              | Yes       | [src](src/network/recv.c)                             | Mapped to `SYS_recvfrom` approach                           |
| `send()`              | Yes       | [src](src/network/send.c)                             | Mapped to `SYS_sendto` approach                             |
| `recvfrom()`          | Yes       | [src](src/network/recvfrom.c)                         |                                                             |
| `sendto()`            | Yes       | [src](src/network/sendto.c)                           |                                                             |
| `recvmsg()`           | Yes       | [src](src/network/recvmsg.c)                          | Simplified for `struct msghdr`                              |
| `sendmsg()`           | Yes       | [src](src/network/sendmsg.c)                          | Simplified for `struct msghdr`                              |
| `getaddrinfo()`       | Yes       | [src](src/network/getaddrinfo.c)                      | Fake/facade logic, real DNS off-host                        |
| `freeaddrinfo()`      | Yes       | [src](src/network/freeaddrinfo.c)                     | Stub                                                        |
| `getnameinfo()`       | Yes       | [src](src/network/getnameinfo.c)                      | Fake/facade logic                                           |
| `poll()`              | Yes       | [src](src/network/poll.c)                             | In/out pointer for `struct pollfd` array                    |
| `select()`            | Yes       | [src](src/network/select.c)                           | In/out `fd_set`, simplified                                 |
| `shutdown()`          | Yes       | [src](src/network/shutdown.c)                         |                                                             |
| `setsockopt()`        | Yes       | [src](src/network/setsockopt.c)                       | Some details simplified                                     |
| `getsockopt()`        | Yes       | [src](src/network/getsockopt.c)                       | Some details simplified                                     |
| `inet_aton()`         | Yes       | [src](src/network/inet_aton.c)                        | Fake/facade for text->`in_addr`                             |
| `inet_ntoa()`         | Yes       | [src](src/network/inet_ntoa.c)                        | Similar approach                                            |
| `inet_pton()`         | Yes       | [src](src/network/inet_pton.c)                        |                                                             |
| `inet_ntop()`         | Yes       | [src](src/network/inet_ntop.c)                        |                                                             |
| `gethostname()`       | Yes       | [src](src/network/gethostname.c)                      | Fake/facade                                                 |
| `socketpair()`        | Yes       | [src](src/network/socketpair.c)                       | Possibly incomplete example, see notes                      |
| `ioctl()`             | Yes       | [src](src/network/ioctl.c)                            | Variation for varargs, partial                              |
| `fcntl()`             | No       | [src](src/network/fcntl.c)                            | Similar partial approach                                    |
| `epoll_create()`      | Yes       | [src](src/network/epoll_create.c)                     | Linux-specific                                              |
| `epoll_create1()`     | Yes       | [src](src/network/epoll_create1.c)                    | Linux-specific                                              |
| `epoll_ctl()`         | Yes       | [src](src/network/epoll_ctl.c)                        | Linux-specific, partial usage                               |
| `epoll_wait()`        | Yes       | [src](src/network/epoll_wait.c)                       | Linux-specific                                              |
| `eventfd()`           | Yes       | [src](src/network/eventfd.c)                          | Linux-specific, partial                                     |
| `getpeername()`       | Yes       | [src](src/network/getpeername.c)                      | Similar to `getsockname`                                    |
| `getsockname()`       | Yes       | [src](src/network/getsockname.c)                      | Implementation above                                        |
| `sendfile()`          | Yes       | [src](src/network/sendfile.c)                         | Provided above                                              |
| `readv()`             | Yes       | [src](src/network/readv.c)                            | Implementation above                                        |
| `writev()`            | Yes       | [src](src/network/writev.c)                           | Similar to `readv`                                          |
| `splice()`            | No       | [src](src/network/splice.c)                           | Linux-specific, partial approach                            |
| `tee()`               | No       | [src](src/network/tee.c)                              | Linux-specific                                              |
| `vmsplice()`          | No       | [src](src/network/vmsplice.c)                         | Linux-specific                                              |
| `getifaddrs()`        | No       | [src](src/network/getifaddrs.c)                       | Stub/fake, requires `<ifaddrs.h>`                           |
| `freeifaddrs()`       | Yes       | [src](src/network/freeifaddrs.c)                      | Stub/fake, requires `<ifaddrs.h>`                           |
| `if_nametoindex()`    | Yes       | [src](src/network/if_nametoindex.c)                   | Requires `<net/if.h>`, partial                              |
| `if_indextoname()`    | Yes       | [src](src/network/if_indextoname.c)                   | Requires `<net/if.h>`, partial                              |
| `if_nameindex()`      | No       | [src](src/network/if_nameindex.c)                     | Requires `<net/if.h>`, partial                              |
| `if_freenameindex()`  | Yes       | [src](src/network/if_freenameindex.c)                 | Requires `<net/if.h>`, partial                              |
| `pselect()`           | No       | [src](src/network/pselect.c)                          | Similar to `select`                                         |
| `epoll_pwait()`       | Yes       | [src](src/network/epoll_pwait.c)                      | Linux-specific                                              |
| `sendmmsg()`          | No       | [src](src/network/sendmmsg.c)                         | Linux-specific, partial for msghdr array                    |
| `recvmmsg()`          | No       | [src](src/network/recvmmsg.c)                         | Linux-specific, partial for msghdr array                    |
| `getprotobyname()`    | No       | [src](src/network/getprotobyname.c)                   | Old library call, partial stub                              |
| `getprotobynumber()`  | No       | [src](src/network/getprotobynumber.c)                 | Old library call, partial stub                              |
| `getservbyname()`     | No       | [src](src/network/getservbyname.c)                    | Old library call, partial stub                              |
| `getservbyport()`     | No       | [src](src/network/getservbyport.c)                    | Old library call, partial stub                              |
| `hstrerror()`         | No       | [src](src/network/hstrerror.c)                        | Obsolete, partial stub                                      |
| `inet_makeaddr()`     | Yes       | [src](src/network/inet_makeaddr.c)                    | IPv4 creation, partial library code                         |
| `inet_lnaof()`        | Yes       | [src](src/network/inet_lnaof.c)                       |                                                             |
| `inet_netof()`        | No       | [src](src/network/inet_netof.c)                       |                                                             |
| `inet_network()`      | No       | [src](src/network/inet_network.c)                     |                                                             |


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

| Function            | Supported | Source                     | Notes                               | Original Reference      |
|---------------------|-----------|---------------------------|--------------------------------------|-------------------------|
| `acos()`            | Yes       | src/math/acos.c           | C89 math                             | C89 / C99               |
| `acosh()`           | Yes       | src/math/acosh.c          | C99 math                             | C99                     |
| `asin()`            | Yes       | src/math/asin.c           | C89 math                             | C89 / C99               |
| `asinh()`           | Yes       | src/math/asinh.c          | C99 math                             | C99                     |
| `atan()`            | Yes       | src/math/atan.c           | C89 math                             | C89 / C99               |
| `atan2()`           | Yes       | src/math/atan2.c          | C89 math                             | C89 / C99               |
| `atanh()`           | Yes       | src/math/atanh.c          | C99 math                             | C99                     |
| `cbrt()`            | Yes       | src/math/cbrt.c           | C99 math                             | C99                     |
| `ceil()`            | Yes       | src/math/ceil.c           | C89 math                             | C89 / C99               |
| `copysign()`        | Yes       | src/math/copysign.c       | C99 math                             | C99                     |
| `cos()`             | Yes       | src/math/cos.c            | C89 math                             | C89 / C99               |
| `cosf()`            | Yes       | src/math/cosf.c           | Float version                        | C99                     |
| `cosh()`            | Yes       | src/math/cosh.c           | C89 math                             | C89 / C99               |
| `exp()`             | Yes       | src/math/exp.c            | C89 math                             | C89 / C99               |
| `fabs()`            | Yes       | src/math/fabs.c           | C89 math                             | C89 / C99               |
| `floor()`           | Yes       | src/math/floor.c          | C89 math                             | C89 / C99               |
| `fma()`             | Yes       | src/math/fma.c            | Fused multiply-add (C11)             | C99 / C11               |
| `fmax()`            | Yes       | src/math/fmax.c           | C99 math                             | C99                     |
| `fmin()`            | Yes       | src/math/fmin.c           | C99 math                             | C99                     |
| `fmod()`            | Yes       | src/math/fmod.c           | C89 math                             | C89 / C99               |
| `frexp()`           | Yes       | src/math/frexp.c          | C89 math                             | C89 / C99               |
| `hypot()`           | Yes       | src/math/hypot.c          | C89 math                             | C89 / C99               |
| `ilogb()`           | Yes       | src/math/ilogb.c          | C99 math                             | C99                     |
| `ldexp()`           | Yes       | src/math/ldexp.c          | C89 math                             | C89 / C99               |
| `log()`             | Yes       | src/math/log.c            | C89 math                             | C89 / C99               |
| `log10()`           | Yes       | src/math/log10.c          | C89 math                             | C89 / C99               |
| `log1p()`           | Yes       | src/math/log1p.c          | C99 math                             | C99                     |
| `log2()`            | Yes       | src/math/log2.c           | C99 math                             | C99                     |
| `logb()`            | Yes       | src/math/logb.c           | C99 math                             | C99                     |
| `modf()`            | Yes       | src/math/modf.c           | C89 math                             | C89 / C99               |
| `nearbyint()`       | Yes       | src/math/nearbyint.c      | C99 rounding                         | C99                     |
| `pow()`             | Yes       | src/math/pow.c            | C89 math                             | C89 / C99               |
| `remainder()`       | Yes       | src/math/remainder.c      | C99 math                             | C99                     |
| `remquo()`          | Yes       | src/math/remquo.c         | C99 math                             | C99                     |
| `round()`           | Yes       | src/math/round.c          | C99 rounding                         | C99                     |
| `scalbn()`          | Yes       | src/math/scalbn.c         | C99 scaling                          | C99                     |
| `signbit()`         | Yes       | (macro in <math.h>)       | Macro in many libs                   | C99 / builtin           |
| `sin()`             | Yes       | src/math/sin.c            | C89 math                             | C89 / C99               |
| `sinh()`            | Yes       | src/math/sinh.c           | C89 math                             | C89 / C99               |
| `sqrt()`            | Yes       | src/math/sqrt.c           | C89 math                             | C89 / C99               |
| `tan()`             | Yes       | src/math/tan.c            | C89 math                             | C89 / C99               |
| `tanh()`            | Yes       | src/math/tanh.c           | C89 math                             | C89 / C99               |
| `trunc()`           | Yes       | src/math/trunc.c          | C99 math                             | C99                     |
| `memcpy()`          | Yes       | src/string/memcpy.c       | C89 string                           | C89                     |
| `memmove()`         | Yes       | src/string/memmove.c      | C89 string                           | C89                     |
| `memset()`          | Yes       | src/string/memset.c       | C89 string                           | C89                     |
| `memcmp()`          | Yes       | src/string/memcmp.c       | C89 string                           | C89                     |
| `memchr()`          | Yes       | src/string/memchr.c       | C89 string                           | C89                     |
| `strcpy()`          | Yes       | src/string/strcpy.c       | C89 string                           | C89                     |
| `strncpy()`         | Yes       | src/string/strncpy.c      | C89 string                           | C89                     |
| `strcat()`          | Yes       | src/string/strcat.c       | C89 string                           | C89                     |
| `strncat()`         | Yes       | src/string/strncat.c      | C89 string                           | C89                     |
| `strcmp()`          | Yes       | src/string/strcmp.c       | C89 string                           | C89                     |
| `strncmp()`         | Yes       | src/string/strncmp.c      | C89 string                           | C89                     |
| `strchr()`          | Yes       | src/string/strchr.c       | C89 string                           | C89                     |
| `strrchr()`         | Yes       | src/string/strrchr.c      | C89 string                           | C89                     |
| `strstr()`          | Yes       | src/string/strstr.c       | C89 string                           | C89                     |
| `strnlen()`         | Yes       | src/string/strnlen.c      | POSIX extension                      | POSIX / C99 extension   |
| `strlen()`          | Yes       | src/string/strlen.c       | C89 string                           | C89                     |
| `strdup()`          | Yes       | src/string/strdup.c       | POSIX extension                      | POSIX                   |
| `strcasecmp()`      | Yes       | src/string/strcasecmp.c   | POSIX extension                      | POSIX                   |
| `strtok()`          | Yes       | src/string/strtok.c       | C89 string                           | C89                     |
| `strerror()`        | Yes       | src/string/strerror.c     | Maps error code to message           | C89 / POSIX (but no sys)|
| `strxfrm()`         | Yes       | src/string/strxfrm.c      | Locale transform (pure userland)     | C89                     |
| `bcmp()`            | Yes       | src/string/bcmp.c         | POSIX/BSD extension                  | POSIX/BSD               |
| `bzero()`           | Yes       | src/string/bzero.c        | Deprecated BSD extension             | BSD                     |
| `strcasecmp_l()`    | Yes       | src/string/strcasecmp_l.c | Locale version (still userland)      | POSIX locale extension  |
| `strncasecmp()`     | Yes       | src/string/strncasecmp.c  | POSIX extension                      | POSIX                   |
| `strncasecmp_l()`   | Yes       | src/string/strncasecmp_l.c| Locale version (still userland)      | POSIX locale extension  |
| `strcoll()`         | Yes       | src/string/strcoll.c      | Locale compare (still userland)      | C89 / XSI              |
| `wcscpy()`          | Yes       | src/wchar/wcscpy.c        | Wide char string                     | C95 / C99               |
| `wcscmp()`          | Yes       | src/wchar/wcscmp.c        | Wide char string                     | C95 / C99               |
| `wcscat()`          | Yes       | src/wchar/wcscat.c        | Wide char string                     | C95 / C99               |
| `wcslen()`          | Yes       | src/wchar/wcslen.c        | Wide char string                     | C95 / C99               |
| `wmemcmp()`         | Yes       | src/wchar/wmemcmp.c       | Wide char version of memcmp          | C95 / C99               |
| `wmemcpy()`         | Yes       | src/wchar/wmemcpy.c       | Wide char version of memcpy          | C95 / C99               |
| `btowc()`           | Yes       | src/ctype/btowc.c         | Single byte to wide char             | C95 / C99               |
| `wctob()`           | Yes       | src/ctype/wctob.c         | Wide char to single byte             | C95 / C99               |
| `isalpha()`         | Yes       | src/ctype/isalpha.c       | C89 ctype                            | C89                     |
| `isdigit()`         | Yes       | src/ctype/isdigit.c       | C89 ctype                            | C89                     |
| `isalnum()`         | Yes       | src/ctype/isalnum.c       | C89 ctype                            | C89                     |
| `islower()`         | Yes       | src/ctype/islower.c       | C89 ctype                            | C89                     |
| `isupper()`         | Yes       | src/ctype/isupper.c       | C89 ctype                            | C89                     |
| `isblank()`         | Yes       | src/ctype/isblank.c       | C99 ctype extension                  | C99                     |
| `isspace()`         | Yes       | src/ctype/isspace.c       | C89 ctype                            | C89                     |
| `ispunct()`         | Yes       | src/ctype/ispunct.c       | C89 ctype                            | C89                     |
| `iscntrl()`         | Yes       | src/ctype/iscntrl.c       | C89 ctype                            | C89                     |
| `isxdigit()`        | Yes       | src/ctype/isxdigit.c      | C89 ctype                            | C89                     |
| `isgraph()`         | Yes       | src/ctype/isgraph.c       | C89 ctype                            | C89                     |
| `isprint()`         | Yes       | src/ctype/isprint.c       | C89 ctype                            | C89                     |
| `tolower()`         | Yes       | src/ctype/tolower.c       | C89 ctype                            | C89                     |
| `toupper()`         | Yes       | src/ctype/toupper.c       | C89 ctype                            | C89                     |
| `toascii()`         | Yes       | src/ctype/toascii.c       | Non-standard/BSD macro               | BSD extension           |
| `abs()`             | Yes       | src/stdlib/abs.c          | C89 stdlib                           | C89                     |
| `labs()`            | Yes       | src/stdlib/labs.c         | C89 stdlib                           | C89                     |
| `llabs()`           | Yes       | src/stdlib/llabs.c        | C99 stdlib                           | C99                     |
| `atoi()`            | Yes       | src/stdlib/atoi.c         | C89 stdlib                           | C89                     |
| `atol()`            | Yes       | src/stdlib/atol.c         | C89 stdlib                           | C89                     |
| `atoll()`           | Yes       | src/stdlib/atoll.c        | C99 stdlib                           | C99                     |
| `strtol()`          | Yes       | src/stdlib/strtol.c       | C89 stdlib                           | C89                     |
| `strtoul()`         | Yes       | src/stdlib/strtoul.c      | C89 stdlib                           | C89                     |
| `strtoll()`         | Yes       | src/stdlib/strtoll.c      | C99 stdlib                           | C99                     |
| `strtoull()`        | Yes       | src/stdlib/strtoull.c     | C99 stdlib                           | C99                     |
| `strtod()`          | Yes       | src/stdlib/strtod.c       | C89 stdlib                           | C89                     |
| `strtof()`          | Yes       | src/stdlib/strtof.c       | C99 float parse                      | C99                     |
| `strtold()`         | Yes       | src/stdlib/strtold.c      | C99 long double parse                | C99                     |
| `calloc()`          | Yes       | src/stdlib/calloc.c       | Typically pure userland, though...   | (Implementation detail) |
| `malloc()`          | ???       | src/malloc/ (uses brk/sbrk?) | *May or may not* use syscalls    | Implementation detail    |
| `free()`            | ???       | src/malloc/ (free.c)      | Ties to memory arena, might call sbrk| Implementation detail    |
| `realloc()`         | ???       | src/malloc/ (realloc.c)   | Possibly calls sbrk/mmap            | Implementation detail    |
| `qsort()`           | Yes       | src/stdlib/qsort.c        | Pure user-level sort                | C89                     |
| `bsearch()`         | Yes       | src/stdlib/bsearch.c      | Pure user-level search              | C89                     |
| `div()`             | Yes       | src/stdlib/div.c          | Returns quotient/remainder struct   | C89                     |
| `ldiv()`            | Yes       | src/stdlib/ldiv.c         | Long version                        | C89                     |
| `lldiv()`           | Yes       | src/stdlib/lldiv.c        | Long long version                   | C99                     |
| `mblen()`           | Yes       | src/stdlib/mblen.c        | Multi-byte to wide char logic       | C89 / locale            |
| `mbtowc()`          | Yes       | src/stdlib/mbtowc.c       | Multi-byte to wide char             | C89 / locale            |
| `wctomb()`          | Yes       | src/stdlib/wctomb.c       | Wide char to multi-byte             | C89 / locale            |
| `rand()`            | Yes       | src/prng/rand.c           | Basic PRNG (not sysrandom)          | C89                     |
| `srand()`           | Yes       | src/prng/rand.c           | Seeds the above PRNG                | C89                     |
| `drand48()`         | Yes       | src/prng/drand48.c        | POSIX-ish random, purely userland   | POSIX                   |
| `erand48()`         | Yes       | src/prng/erand48.c        | POSIX-ish random, purely userland   | POSIX                   |
| `lcong48()`         | Yes       | src/prng/lcong48.c        | POSIX-ish random, purely userland   | POSIX                   |
| `srand48()`         | Yes       | src/prng/srand48.c        | POSIX-ish random, purely userland   | POSIX                   |
| `strsep()`          | Yes       | src/string/strsep.c       | Splits string by delimiter          | BSD/POSIX extension     |
| `strsignal()`       | Yes       | src/string/strsignal.c    | Maps signal # to name (table-based) | POSIX (no syscalls)     |
| `aligned_alloc()`   | ???       | src/stdlib/aligned_alloc.c| Usually pure userland + a backend   | C11, might call malloc  |
| `wmemcmp()`         | Yes       | src/wchar/wmemcmp.c       | Compare wide strings                | C95 / C99               |
| `wmemmove()`        | Yes       | src/wchar/wmemmove.c      | Wide char memmove                   | C95 / C99               |
| `wcscmp()`          | Yes       | src/wchar/wcscmp.c        | Compare wide strings                | C95 / C99               |
| `wcscspn()`         | Yes       | src/wchar/wcscspn.c       | Wide char strcspn analog            | C95 / C99               |
| `wcsdup()`          | Yes       | src/wchar/wcsdup.c        | Wide char strdup                    | POSIX wide extension    |
| `wcslcat()`         | ???       | Not always in standard    | BSD extension, if present           | BSD                     |
| `wcslcpy()`         | ???       | Not always in standard    | BSD extension, if present           | BSD                     |
| `wcstok()`          | Yes       | src/wchar/wcstok.c        | Wide char version of strtok         | C95 / C99               |
| `vsnprintf()`       | Yes       | src/stdio/vsnprintf.c     | Print to string buffer (userland)   | C99                     |
| `snprintf()`        | Yes       | src/stdio/snprintf.c      | Print to string buffer (userland)   | C99                     |
| `sprintf()`         | Yes       | src/stdio/sprintf.c       | Print to string buffer (userland)   | C89                     |
| `sscanf()`          | Yes       | src/stdio/sscanf.c        | Scan from string buffer (userland)  | C89                     |
| `vfscanf()`         | ???       | Typically does read from FILE, might be sys if not careful | C89 |
| `vsscanf()`         | Yes       | src/stdio/vsscanf.c       | Parse from memory buffer, userland  | C99                     |
| `strcoll_l()`       | Yes       | src/string/strcoll_l.c    | Locale-based string compare         | XSI / POSIX extension   |
| `strxfrm_l()`       | Yes       | src/string/strxfrm_l.c    | Locale-based transform              | XSI / POSIX extension   |
| `wcscoll()`         | Yes       | src/wchar/wcscoll.c       | Wide char locale compare            | XSI / POSIX extension   |
| `wcsxfrm()`         | Yes       | src/wchar/wcsxfrm.c       | Wide char locale transform          | XSI / POSIX extension   |
| `wcwidth()`         | Yes       | src/ctype/wcwidth.c       | Width of wide char for display      | POSIX                   |
| `wcswidth()`        | Yes       | src/wchar/wcswidth.c      | Width of wide string for display    | POSIX                   |
| `ecvt()`, `fcvt()`  | ???       | src/stdio/ecvt.c,fcvt.c   | Obsolete float-to-string, userland  | Legacy (not always)     |
| `gcvt()`            | ???       | src/stdio/gcvt.c          | Obsolete float-to-string, userland  | Legacy (not always)     |
| `finite()`          | Yes       | src/math/finite.c         | Checks if float is finite           | POSIX / C99             |
| `isinf()`           | Yes       | src/math/isinf.c          | Checks infinity                     | C99                     |
| `isnan()`           | Yes       | src/math/isnan.c          | Checks NaN                          | C99                     |
| `nextafter()`       | Yes       | src/math/nextafter.c      | Next representable float            | C99                     |
| `fegetround()`      | ???       | src/fenv/fegetround.c     | Might use CPU instructions, no sys  | C99 / arch dependent    |
| `fesetround()`      | ???       | src/fenv/fesetround.c     | Might use CPU instructions, no sys  | C99 / arch dependent    |
| `feclearexcept()`   | ???       | src/fenv/feclearexcept.c  | CPU instructions, no sys            | C99 / arch dependent    |
| `fegetexceptflag()` | ???       | src/fenv/fegetexceptflag.c| CPU instructions, no sys            | C99 / arch dependent    |
| `fesetexceptflag()` | ???       | src/fenv/fesetexceptflag.c| CPU instructions, no sys            | C99 / arch dependent    |
| `feraiseexcept()`   | ???       | src/fenv/feraiseexcept.c  | CPU instructions, no sys            | C99 / arch dependent    |
| `fetestexcept()`    | ???       | src/fenv/fetestexcept.c   | CPU instructions, no sys            | C99 / arch dependent    |
| `feholdexcept()`    | ???       | src/fenv/feholdexcept.c   | CPU instructions, no sys            | C99 / arch dependent    |
| `feupdateenv()`     | ???       | src/fenv/feupdateenv.c    | CPU instructions, no sys            | C99 / arch dependent    |
| `scalb()`, `scalbf()`| ???      | src/math/scalb.c, etc.    | Obsolete scale functions, userland  | Legacy / BSD            |
| `gamma()`, `lgamma()`| Yes      | src/math/lgamma.c         | C99 / POSIX math                    | C99, might track sign   |
| `tgamma()`          | Yes       | src/math/tgamma.c         | C99 math                            | C99                     |
| `sincos()`          | ???       | src/math/sincos.c         | GNU extension, purely userland      | GNU ext                 |
| `fenv` macros       | Yes/No    | <fenv.h> macros           | CPU instructions, no syscalls       | C99 / arch dependent    |
| `drand48_r()` etc.  | Yes       | src/prng/drand48_r.c      | Reentrant versions, userland        | POSIX                   |
| `nrand48()`         | Yes       | src/prng/nrand48.c        | Part of drand48 family, userland    | POSIX                   |
| `lrand48()`         | Yes       | src/prng/lrand48.c        | Part of drand48 family, userland    | POSIX                   |
| `mrand48()`         | Yes       | src/prng/mrand48.c        | Part of drand48 family, userland    | POSIX                   |
| `iconv_*()`         | ???       | src/iconv/*               | Character set conversion, userland  | POSIX / XSI             |
| `regex` routines    | ???       | src/regex/*               | Regex engine, purely userland       | POSIX                   |
| `fnmatch()`         | ???       | src/fnmatch/fnmatch.c     | Filename matching, userland         | POSIX                   |
| `glob()`            | ???       | src/glob/glob.c           | Shell-style path expansion (BUT might do readdir => can be sys)  | POSIX   |
| `fmtmsg()`          | ???       | src/stdio/fmtmsg.c        | Formats messages (userland?), POSIX | POSIX                   |
| `psiginfo()`        | ???       | src/signal/psiginfo.c     | Prints signal info (table-based)     | XSI, can be userland    |
| `psignal()`         | ???       | src/signal/psignal.c      | Prints signal name from table        | XSI, userland           |
| `argz_*()`, `envz_*()`| ???     | src/argz, src/envz        | GNU extensions, userland manip       | GNU/BSD ext             |
| `obstack_*()`       | ???       | src/alloc/obstack.c       | GNU extension, userland             | GNU extension           |
| `gnulib` style fns  | ???       | -                          | Various purely user-level expansions | GNU extension           |
| `crypto` stubs?     | ???       | -                          | Some libs have userland crypto       | Implementation detail    |
| `hsearch()`, `tsearch()` etc. | ??? | src/search/ (no syscalls) | POSIX tree/hashtable (userland) | POSIX                   |
| `wctype()`          | Yes       | src/ctype/wctype.c        | Wide char classification, userland  | C95 / C99               |
| `iswalpha()`, `iswdigit()`, etc.| Yes | `src/ctype/isw*.c`    | Wide char ctype family, userland    | C95 / C99               |
| `towupper()`, `towlower()` | Yes | `src/ctype/tow*.c`         | Wide char transform, userland       | C95 / C99               |
| `fmemopen()`        | ???       | src/stdio/fmemopen.c      | Opens a memory buffer as `FILE*`, purely userland if done carefully  | POSIX |
| `open_memstream()`  | ???       | src/stdio/open_memstream.c| Another memory-based stream, userland| POSIX                   |
| `asprintf()`        | ???       | src/stdio/asprintf.c      | Alloc-based sprintf (calls malloc)   | GNU/BSD ext             |
| `dprintf()`         | ???       | src/stdio/dprintf.c       | Writes to FD (=> might do syscalls)  | POSIX                   |
| `vasprintf()`       | ???       | src/stdio/vasprintf.c     | Alloc-based vsnprintf (calls malloc) | GNU/BSD ext             |
| `vdprintf()`        | ???       | src/stdio/vdprintf.c      | Writes to FD (=> might do syscalls)  | POSIX                   |
| `strtoimax()`, `strtoumax()`|Yes| src/stdlib/strtoimax.c, etc. | Integer parse, userland           | C99 / inttypes.h        |
| `imaxabs()`, `imaxdiv()` |Yes   | src/stdlib/imaxabs.c etc.  | intmax_t versions, userland         | C99 / inttypes.h        |
| `wcstod()`, `wcstof()`, `wcstold()`|Yes| src/wchar/wcstod.c etc.| Wide char to double float parse     | C99                     |
| `wcstoimax()`, `wcstoumax()`|Yes| src/wchar/wcstoimax.c etc.| Wide char integer parse, userland   | C99 / inttypes.h        |
| `mbsinit()`         | Yes       | src/multibyte/mbsinit.c   | Checks if multibyte state is initial| C99                     |
| `mbrlen()`, `mbrtowc()`, `wcrtomb()` |Yes| src/multibyte/        | Multi-byte state conversions        | C99 locale              |
| `strcoll()`         | Yes       | src/string/strcoll.c      | Locale compare, userland            | C89 / XSI               |
| `strftime()`        | ???       | src/time/strftime.c       | Formats time as string (no syscalls unless locale loading) | C89/XSI |
| `strptime()`        | ???       | src/time/strptime.c       | Parse time from string (userland)   | XSI / POSIX extension   |
| `wcsftime()`        | ???       | src/time/wcsftime.c       | Wide-char time format (userland)    | XSI / POSIX extension   |
| `difftime()`        | Yes       | src/time/difftime.c       | Just subtracts two time_t values, pure userland | C89   |
| ... etc.            | ...       | ...                        | Many more small helpers...           | ...                     |

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

