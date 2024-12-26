#include <unistd.h>
#include "wasm_vfs_ffi.h"

int chown(const char *path, uid_t owner, gid_t group)
{
    return wasm_vfs_chown(path, (uint32_t)owner, (uint32_t)group);
}

