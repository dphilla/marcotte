#include <unistd.h>
#include "wasm_vfs_ffi.h"

int access(const char *pathname, int mode)
{
    return wasm_vfs_access(pathname, mode);
}

