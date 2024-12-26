#include <unistd.h>
#include "wasm_vfs_ffi.h"

int close(int fd)
{
    return wasm_vfs_close(fd);
}

