#include <unistd.h>
#include "wasm_vfs_ffi.h"

int chdir(const char *path)
{
    return wasm_vfs_chdir(path);
}

