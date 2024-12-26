#include <unistd.h>
#include "wasm_vfs_ffi.h"

int faccessat(int dirfd, const char *pathname, int mode, int flags)
{
    /* TODO - check posix compat -  ignoring dirfd/flags for now, call wasm_vfs_faccessat if you want. */
    return wasm_vfs_access(pathname, mode);
}

