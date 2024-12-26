#include <sys/stat.h>
#include "wasm_vfs_ffi.h"

int fchmodat(int dirfd, const char *pathname, mode_t mode, int flags)
{
    /* ignoring flags for simplicity */
    (void)flags;
    /* we can do chmod with absolute path or use wasm_vfs_fchmodat if you have that. */
    return wasm_vfs_chmod(pathname, (uint32_t)mode);
}

