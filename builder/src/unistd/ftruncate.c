#include <unistd.h>
#include "wasm_vfs_ffi.h"

int ftruncate(int fd, off_t length)
{
    return wasm_vfs_ftruncate(fd, length);
}

