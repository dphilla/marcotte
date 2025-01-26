#include <unistd.h>
#include "wasm_vfs_ffi.h"

int dup2(int oldfd, int newfd)
{
    return wasm_vfs_dup2(oldfd, newfd);
}

