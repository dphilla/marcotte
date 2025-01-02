#include <fcntl.h>
#include <stdarg.h>
#include "wasm_vfs_ffi.h"

int openat(int dirfd, const char *pathname, int flags, ...)
{
    mode_t mode = 0;

    /* If O_CREAT is set, user code might pass 'mode_t' as an extra arg. */
    if (flags & O_CREAT) {
        va_list ap;
        va_start(ap, flags);
        mode = va_arg(ap, mode_t);
        va_end(ap);
    }

    return wasm_vfs_openat(dirfd, pathname, flags, (unsigned int)mode);
}
