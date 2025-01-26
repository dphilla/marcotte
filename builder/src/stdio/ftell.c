#include <stdio.h>
#include "wasm_vfs_ffi.h"

long ftell(FILE *stream)
{
    if (!stream) return -1L;
    off_t r = wasm_vfs_lseek(stream->fd, 0, 1 /* SEEK_CUR */);
    if (r < 0) {
        stream->error = 1;
        return -1L;
    }
    return (long)r;
}

