#include <sys/stat.h>
#include "wasm_vfs_ffi.h"

int mkdir(const char *pathname, mode_t mode)
{
    return wasm_vfs_mkdir(pathname, (uint32_t)mode);
}

