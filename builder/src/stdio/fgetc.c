#include <stdio.h>
#include "wasm_vfs_ffi.h"

int fgetc(FILE *stream)
{
    if (!stream) return EOF;
    unsigned char c;
    ssize_t ret = wasm_vfs_read(stream->fd, &c, 1);
    if (ret == 0) {
        stream->eof = 1;
        return EOF;
    }
    if (ret < 0) {
        stream->error = 1;
        return EOF;
    }
    return c;
}

