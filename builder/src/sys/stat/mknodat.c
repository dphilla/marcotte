#include <sys/stat.h>
#include <errno.h>

int mknodat(int dirfd, const char *pathname, mode_t mode, dev_t dev)
{
    (void)dirfd; (void)pathname; (void)mode; (void)dev;
    errno = ENOSYS;
    return -1;
}

