#include <stdio.h>
#include "wasm_vfs_ffi.h"

int fputc(int c, FILE *stream)
{
    if (!stream) return EOF;
    unsigned char ch = c;
    ssize_t ret = wasm_vfs_write(stream->fd, &ch, 1);
    if (ret < 1) {
        stream->error = 1;
        return EOF;
    }
    return (int)ch;
}

