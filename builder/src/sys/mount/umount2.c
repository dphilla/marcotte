#include <sys/mount.h>
#include <errno.h>

int umount2(const char *target, int flags)
{
    (void)target; (void)flags;
    errno = ENOSYS;
    return -1;
}

