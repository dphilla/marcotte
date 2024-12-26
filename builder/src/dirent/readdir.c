#include <dirent.h>
#include <unistd.h>      /* for read() or getdents calls */
#include <string.h>      /* for memcpy() */
#include "wasm_vfs_ffi.h"

/* We'll read dirents from wasm_vfs_getdents or getdents64. */

struct dirent *readdir(DIR *dirp)
{
    static struct dirent ent;  /* not thread-safe, but typical approach */

    if (!dirp) return NULL;

    /* If buffer is exhausted, refill. */
    if (dirp->buf_pos >= dirp->buf_end) {
        int n = wasm_vfs_getdents(dirp->fd, dirp->buffer, sizeof(dirp->buffer));
        if (n <= 0) {
            return NULL;  /* no more entries */
        }
        dirp->buf_pos = 0;
        dirp->buf_end = n;
    }

    if (dirp->buf_pos + (int)sizeof(struct dirent) > dirp->buf_end) {
        return NULL; /* truncated / no more aligned entries */
    }

    /* Copy out one dirent from the buffer. */
    memcpy(&ent, &dirp->buffer[dirp->buf_pos], sizeof(struct dirent));
    dirp->buf_pos += sizeof(struct dirent);

    if (ent.d_reclen == 0) {
        return NULL;  /* no valid data */
    }
    return &ent;
}

