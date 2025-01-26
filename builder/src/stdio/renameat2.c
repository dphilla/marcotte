#include <unistd.h>
#include "wasm_vfs_ffi.h"

int renameat2(int olddirfd, const char *oldpath, int newdirfd,
              const char *newpath, unsigned int flags)
{
    /* ignoring flags, just rename. */
    return wasm_vfs_rename(oldpath, newpath);
}

