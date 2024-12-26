#include <fcntl.h>
#include <errno.h>
#include "wasm_vfs_ffi.h"

/*
  For a fully correct fcntl, you'd handle F_GETFD, F_SETFD, F_SETFL, file locks, etc.
  for now, a minimal approach
*/

//TODO - implement in VFS, approximate behavior sans threads
int fcntl(int fd, int cmd, ...)
{
    switch (cmd) {
    case F_GETFD:
    case F_SETFD:
    case F_GETFL:
    case F_SETFL:
        return 0;
    default:
        errno = EINVAL;
        return -1;
    }
}

