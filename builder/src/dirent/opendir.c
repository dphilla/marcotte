#include <dirent.h>
#include <fcntl.h>      /* O_RDONLY, O_DIRECTORY  */
#include <stdlib.h>     /* malloc() */
#include <string.h>     /* memset() */
#include <unistd.h>     /* open() */
#include "wasm_vfs_ffi.h"

DIR *opendir(const char *name)
{
    /* TODO - double check this : Typically open() with O_DIRECTORY. */
    int fd = wasm_vfs_open(name, O_RDONLY, 0);
    if (fd < 0) return NULL;

    DIR *dirp = (DIR*)malloc(sizeof(DIR));
    if (!dirp) {
        close(fd);
        return NULL;
    }
    dirp->fd = fd;
    dirp->buf_pos = 0;
    dirp->buf_end = 0;
    memset(dirp->buffer, 0, sizeof(dirp->buffer));
    return dirp;
}

