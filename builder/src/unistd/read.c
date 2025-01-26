#include <unistd.h>
#include "wasm_vfs_ffi.h"

ssize_t read(int fd, void *buf, size_t count)
{
    return wasm_vfs_read(fd, buf, count);
}

