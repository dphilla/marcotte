#include <unistd.h>
#include "wasm_vfs_ffi.h"

int fchownat(int dirfd, const char *pathname, uid_t owner, gid_t group, int flags)
{
    (void)dirfd; (void)flags;
    return wasm_vfs_chown(pathname, (uint32_t)owner, (uint32_t)group);
}

