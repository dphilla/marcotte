#include <unistd.h>
#include "wasm_vfs_ffi.h"

ssize_t splice(int fd_in, off_t *off_in,
               int fd_out, off_t *off_out,
               size_t len, unsigned int flags)
{
    return wasm_vfs_splice(fd_in, off_in, fd_out, off_out, len, flags);
}

