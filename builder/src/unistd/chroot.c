#include <unistd.h>
#include <errno.h>

int chroot(const char *path)
{
    /* Not typically supported in Wasm-VFS. */

   // TODO - IMPLEMENT in vfs - possibly via module spawn, or... look at native impls
    (void)path;
    errno = ENOSYS;
    return -1;
}

