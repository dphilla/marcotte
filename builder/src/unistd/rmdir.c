#include <unistd.h>
#include "wasm_vfs_ffi.h"

int rmdir(const char *pathname)
{
    return wasm_vfs_rmdir(pathname);
}

