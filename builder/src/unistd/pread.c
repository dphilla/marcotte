#include <unistd.h>
#include "wasm_vfs_ffi.h"

ssize_t pread(int fd, void *buf, size_t count, off_t offset)
{
    return wasm_vfs_pread64(fd, buf, count, offset);
}


