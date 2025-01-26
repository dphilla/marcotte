#include <stdio.h>
#include "string.h"
#include "wasm_vfs_ffi.h"

int fputs(const char *s, FILE *stream)
{
    if (!stream) return EOF;
    size_t len = strlen(s);
    ssize_t ret = wasm_vfs_write(stream->fd, s, len);
    if (ret < (ssize_t)len) {
        stream->error = 1;
        return EOF;
    }
    return (int)ret;
}

