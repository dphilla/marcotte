#include <unistd.h>
#include "wasm_vfs_ffi.h"

char *getcwd(char *buf, size_t size)
{
    return wasm_vfs_getcwd(buf, size);
}

