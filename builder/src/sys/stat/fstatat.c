#include <sys/stat.h>
#include "wasm_vfs_ffi.h"

int fstatat(int dirfd, const char *pathname, struct stat *buf, int flags)
{
    return wasm_vfs_fstatat(dirfd, pathname, (void*)buf, flags);
}

