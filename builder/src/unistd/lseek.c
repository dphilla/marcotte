#include <unistd.h>
#include "wasm_vfs_ffi.h"

off_t lseek(int fd, off_t offset, int whence)
{
    return wasm_vfs_lseek(fd, offset, whence);
}

