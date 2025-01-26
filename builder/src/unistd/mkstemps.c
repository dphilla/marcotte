#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "wasm_vfs_ffi.h"

/* mkstemps is like mkstemp but allows for a suffix. */
int mkstemps(char *template, int suffix_len)
{
    if (!template) {
        errno = EINVAL;
        return -1;
    }
    size_t len = strlen(template);
    if (len < (size_t)(6 + suffix_len)) {
        errno = EINVAL;
        return -1;
    }
    char *p = strstr(template, "XXXXXX");
    if (!p) {
        errno = EINVAL;
        return -1;
    }
    /* naive approach again */
    p[0] = '1'; p[1] = '2'; p[2] = '3'; p[3] = '4'; p[4] = '5'; p[5] = '6';

    int fd = wasm_vfs_open(template, O_RDWR | O_CREAT | O_EXCL, 0600);
    if (fd < 0) return -1;
    return fd;
}

