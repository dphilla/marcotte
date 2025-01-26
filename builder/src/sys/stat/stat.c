#include <sys/stat.h>
#include "wasm_vfs_ffi.h"

int stat(const char *path, struct stat *buf)
{
    return wasm_vfs_stat(path, (void*)buf);
}

