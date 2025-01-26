#include <stdio.h>
#include "wasm_vfs_ffi.h"

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    if (!stream) return 0;
    size_t total = size * nmemb;
    if (total == 0) return 0;

    ssize_t ret = wasm_vfs_read(stream->fd, ptr, total);
    if (ret < 0) {
        stream->error = 1;
        return 0;
    }
    if (ret == 0) {
        stream->eof = 1;
        return 0;
    }
    return (size_t)ret / size;
}

