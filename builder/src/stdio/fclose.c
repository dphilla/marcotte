#include <stdio.h>
#include <stdlib.h>
#include "wasm_vfs_ffi.h"

int fclose(FILE *stream)
{
    if (!stream) return -1;
    int r = wasm_vfs_close(stream->fd);
    free(stream);
    return r;
}

