#include <sys/mount.h>
#include <errno.h>

int umount(const char *target)
{
    (void)target;
    errno = ENOSYS;
    return -1;
}

