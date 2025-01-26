#include <unistd.h>
#include "wasm_vfs_ffi.h"

int renameat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath)
{
    /* ignoring dirfds for simplicity, call rename anyway. */
    return wasm_vfs_rename(oldpath, newpath);
}

