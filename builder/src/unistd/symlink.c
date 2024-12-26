#include <unistd.h>
#include "wasm_vfs_ffi.h"

int symlink(const char *target, const char *linkpath)
{
    return wasm_vfs_symlink(target, linkpath);
}

