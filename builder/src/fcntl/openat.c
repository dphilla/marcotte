#include <fcntl.h>
#include "wasm_vfs_ffi.h"

int openat(int dirfd, const char *pathname, int flags, mode_t mode)
{
    return wasm_vfs_openat(dirfd, pathname, flags, (unsigned int)mode);
}

