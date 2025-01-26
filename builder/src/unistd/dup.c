#include <unistd.h>
#include "wasm_vfs_ffi.h"

int dup(int oldfd)
{
    return wasm_vfs_dup(oldfd);
}

