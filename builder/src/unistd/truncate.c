#include <unistd.h>
#include "wasm_vfs_ffi.h"

int truncate(const char *path, off_t length)
{
    return wasm_vfs_truncate(path, length);
}

