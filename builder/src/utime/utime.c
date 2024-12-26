#include <utime.h>
#include <errno.h>

/*TODO: wasm_vfs function to set file times, use it. Otherwise stub. */

int utime(const char *filename, const struct utimbuf *times)
{
    /* Not implemented in the minimal in-memory FS example unless you store atime, mtime. */
    (void)filename; (void)times;
    errno = ENOSYS;
    return -1;
}

