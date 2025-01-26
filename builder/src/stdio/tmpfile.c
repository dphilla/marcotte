#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "wasm_vfs_ffi.h"

FILE *tmpfile(void)
{
    /* create a random file name in /tmp, open it O_RDWR | O_CREAT | O_EXCL, then unlink it. */
    char name[64];
    static unsigned counter = 0;
    snprintf(name, sizeof(name), "/tmp/tmpfile_%u", counter++);
    int fd = wasm_vfs_open(name, O_RDWR | O_CREAT | O_EXCL, 0600);
    if (fd < 0) return NULL;
    /* unlink so it disappears after close */
    wasm_vfs_unlink(name);

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

