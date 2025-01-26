#include <unistd.h>
#include "wasm_vfs_ffi.h"

ssize_t readlink(const char *pathname, char *buf, size_t bufsiz)
{
    return wasm_vfs_readlink(pathname, buf, bufsiz);
}

