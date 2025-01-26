#include <unistd.h>
#include "wasm_vfs_ffi.h"

int fchdir(int fd)
{
    return wasm_vfs_fchdir(fd);
}

