#include <unistd.h>
#include <errno.h>
#include "wasm_vfs_ffi.h"

int dup3(int oldfd, int newfd, int flags)
{
    if (oldfd == newfd) {
        errno = EINVAL;
        return -1;
    }
    return wasm_vfs_dup2(oldfd, newfd);
    /* ignore 'flags' in this minimal approach. */
}

