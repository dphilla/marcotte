#include <sys/stat.h>
#include "wasm_vfs_ffi.h"

int fstat(int fd, struct stat *buf)
{
    return wasm_vfs_fstat(fd, (void*)buf);
}

