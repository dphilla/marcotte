#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "wasm_vfs_ffi.h"

FILE *fopen(const char *pathname, const char *mode)
{
    int flags = 0;
    if (strcmp(mode, "r") == 0) {
        flags = O_RDONLY;
    } else if (strcmp(mode, "r+") == 0) {
        flags = O_RDWR;
    } else if (strcmp(mode, "w") == 0) {
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    } else if (strcmp(mode, "w+") == 0) {
        flags = O_RDWR | O_CREAT | O_TRUNC;
    } else if (strcmp(mode, "a") == 0) {
        flags = O_WRONLY | O_CREAT | O_APPEND;
    } else if (strcmp(mode, "a+") == 0) {
        flags = O_RDWR | O_CREAT | O_APPEND;
    } else {
        return NULL; /* unsupported mode */
    }

    int fd = wasm_vfs_open(pathname, flags, 0666);
    if (fd < 0) return NULL;

    FILE *f = malloc(sizeof(FILE));
    if (!f) {
        wasm_vfs_close(fd);
        return NULL;
    }
    f->fd = fd;
    f->eof = 0;
    f->error = 0;
    return f;
}

