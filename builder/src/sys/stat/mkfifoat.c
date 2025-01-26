#include <sys/stat.h>
#include <errno.h>

int mkfifoat(int dirfd, const char *pathname, mode_t mode)
{
    (void)dirfd; (void)pathname; (void)mode;
    errno = ENOSYS;
    return -1;
}

