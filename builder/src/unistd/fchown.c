#include <unistd.h>
#include "wasm_vfs_ffi.h"

int fchown(int fd, uid_t owner, gid_t group)
{
    return wasm_vfs_fchown(fd, (uint32_t)owner, (uint32_t)group);
}

