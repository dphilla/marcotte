#include <sys/stat.h>
#include <errno.h>

int mkfifo(const char *pathname, mode_t mode)
{
    /* TODO - implement this and related in vfs  */
    (void)pathname; (void)mode;
    errno = ENOSYS;
    return -1;
}

