#include <sys/stat.h>
#include "wasm_vfs_ffi.h"

int chmod(const char *path, mode_t mode)
{
    return wasm_vfs_chmod(path, (uint32_t)mode);
}

