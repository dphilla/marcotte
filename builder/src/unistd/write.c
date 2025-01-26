#include <unistd.h>
#include "wasm_vfs_ffi.h"

ssize_t write(int fd, const void *buf, size_t count)
{
    return wasm_vfs_write(fd, buf, count);
}

