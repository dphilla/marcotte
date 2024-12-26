#include <unistd.h>
#include "wasm_vfs_ffi.h"

int unlink(const char *pathname)
{
    return wasm_vfs_unlink(pathname);
}
