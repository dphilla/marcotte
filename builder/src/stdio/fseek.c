#include <stdio.h>
#include "wasm_vfs_ffi.h"

int fseek(FILE *stream, long offset, int whence)
{
    if (!stream) return -1;
    off_t r = wasm_vfs_lseek(stream->fd, offset, whence);
    if (r < 0) {
        stream->error = 1;
        return -1;
    }
    stream->eof = 0;
    return 0;
}

