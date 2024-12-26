#include <unistd.h>
#include "wasm_vfs_ffi.h"

ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count)
{
    return wasm_vfs_sendfile(out_fd, in_fd, offset, count);
}

