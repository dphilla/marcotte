#include <stdio.h>
#include "wasm_vfs_ffi.h"

char *fgets(char *s, int n, FILE *stream)
{
    if (!stream || n <= 1) return NULL;
    int i = 0;
    while (i < n - 1) {
        unsigned char c;
        ssize_t ret = wasm_vfs_read(stream->fd, &c, 1);
        if (ret == 0) {
            if (i == 0) return NULL; /* immediate EOF => return NULL */
            break;
        }
        if (ret < 0) {
            stream->error = 1;
            if (i == 0) return NULL;
            break;
        }
        s[i++] = c;
        if (c == '\n') break;
    }
    s[i] = '\0';
    return s;
}

