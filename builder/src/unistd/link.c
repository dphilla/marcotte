#include <unistd.h>
#include "wasm_vfs_ffi.h"

int link(const char *oldpath, const char *newpath)
{
    return wasm_vfs_link(oldpath, newpath);
}

