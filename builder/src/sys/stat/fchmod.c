#include <sys/stat.h>
#include "wasm_vfs_ffi.h"

int fchmod(int fd, mode_t mode)
{
    return wasm_vfs_fchmod(fd, (uint32_t)mode);
}

