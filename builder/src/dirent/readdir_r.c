#include <dirent.h>
#include <string.h>  /* memcpy() */
#include "wasm_vfs_ffi.h"

/*
  readdir_r is deprecated on many modern systems, but we provide it anyway:
  It's basically a thread-safe version that stores the result in 'entry'
  and returns a pointer in '*result'.
*/

int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result)
{
    if (!dirp || !entry || !result) {
        return -1;  /* EINVAL */
    }

    if (dirp->buf_pos >= dirp->buf_end) {
        int n = wasm_vfs_getdents(dirp->fd, dirp->buffer, sizeof(dirp->buffer));
        if (n <= 0) {
            *result = NULL;
            return 0;
        }
        dirp->buf_pos = 0;
        dirp->buf_end = n;
    }

    if (dirp->buf_pos + (int)sizeof(struct dirent) > dirp->buf_end) {
        *result = NULL;
        return 0;
    }

    memcpy(entry, &dirp->buffer[dirp->buf_pos], sizeof(struct dirent));
    dirp->buf_pos += sizeof(struct dirent);

    if (entry->d_reclen == 0) {
        *result = NULL;
    } else {
        *result = entry;
    }
    return 0;
}

