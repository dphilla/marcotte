#include <unistd.h>
#include "wasm_vfs_ffi.h"

int rename(const char *oldpath, const char *newpath)
{
    return wasm_vfs_rename(oldpath, newpath);
}

