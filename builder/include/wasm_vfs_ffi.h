/* include/wasm_vfs_ffi.h */
#ifndef WASM_VFS_FFI_H
#define WASM_VFS_FFI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>  /* for off_t, ssize_t, etc. */
#include <stdint.h>     /* for uint32_t, etc. */

int     wasm_vfs_open(const char *path, int flags, uint32_t mode);
int     wasm_vfs_close(int fd);
ssize_t wasm_vfs_read(int fd, void *buf, size_t count);
ssize_t wasm_vfs_write(int fd, const void *buf, size_t count);
off_t   wasm_vfs_lseek(int fd, off_t offset, int whence);

int     wasm_vfs_stat(const char *path, void *statbuf);   /* cast to struct stat* */
int     wasm_vfs_fstat(int fd, void *statbuf);
int     wasm_vfs_lstat(const char *path, void *statbuf);
int     wasm_vfs_fstatat(int dirfd, const char *pathname, void *statbuf, int flags);

int     wasm_vfs_unlink(const char *pathname);
int     wasm_vfs_link(const char *oldpath, const char *newpath);
int     wasm_vfs_rename(const char *oldpath, const char *newpath);
int     wasm_vfs_symlink(const char *target, const char *linkpath);
ssize_t wasm_vfs_readlink(const char *path, char *buf, size_t bufsize);

int     wasm_vfs_mkdir(const char *path, uint32_t mode);
int     wasm_vfs_rmdir(const char *path);
int     wasm_vfs_chdir(const char *path);
int     wasm_vfs_fchdir(int fd);
char *  wasm_vfs_getcwd(char *buf, size_t size);

int     wasm_vfs_chmod(const char *path, uint32_t mode);
int     wasm_vfs_fchmod(int fd, uint32_t mode);
int     wasm_vfs_chown(const char *path, uint32_t owner, uint32_t group);
int     wasm_vfs_fchown(int fd, uint32_t owner, uint32_t group);

int     wasm_vfs_access(const char *path, int mode);
int     wasm_vfs_faccessat(int dirfd, const char *path, int mode, int flags);

int     wasm_vfs_dup(int oldfd);
int     wasm_vfs_dup2(int oldfd, int newfd);
int     wasm_vfs_openat(int dirfd, const char *pathname, int flags, uint32_t mode);

ssize_t wasm_vfs_pread64(int fd, void *buf, size_t count, off_t offset);
ssize_t wasm_vfs_pwrite64(int fd, const void *buf, size_t count, off_t offset);
ssize_t wasm_vfs_sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
ssize_t wasm_vfs_splice(int fd_in, off_t *off_in, int fd_out, off_t *off_out, size_t len, unsigned int flags);

int     wasm_vfs_truncate(const char *path, off_t length);
int     wasm_vfs_ftruncate(int fd, off_t length);

int     wasm_vfs_umask(int mask);

int     wasm_vfs_getdents(int fd, void *dirp, size_t count);
int     wasm_vfs_getdents64(int fd, void *dirp, size_t count);

/* For stub functions: */
int     wasm_vfs_mmap_stub(void);
int     wasm_vfs_munmap_stub(void);
int     wasm_vfs_flock_stub(int fd, int operation);
int     wasm_vfs_sync_stub(void);
int     wasm_vfs_fsync_stub(int fd);
int     wasm_vfs_fdatasync_stub(int fd);
int     wasm_vfs_syncfs_stub(int fd);

#ifdef __cplusplus
}
#endif

#endif

