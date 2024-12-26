#include <sys/stat.h>
#include "wasm_vfs_ffi.h"

int lstat(const char *path, struct stat *buf)
{
    return wasm_vfs_lstat(path, (void*)buf);
}

