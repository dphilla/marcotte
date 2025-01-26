#include <fcntl.h>
#include "wasm_vfs_ffi.h"
int creat(const char *pathname, mode_t mode)
{
    /* creat is open with O_WRONLY|O_CREAT|O_TRUNC */
    return wasm_vfs_open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
}

