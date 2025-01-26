#include <unistd.h>
#include "wasm_vfs_ffi.h"

ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset)
{
    return wasm_vfs_pwrite64(fd, buf, count, offset);
}

