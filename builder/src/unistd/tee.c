#include <unistd.h>
#include <errno.h>

ssize_t tee(int fd_in, int fd_out, size_t len, unsigned int flags)
{
    (void)fd_in; (void)fd_out; (void)len; (void)flags;
    errno = ENOSYS;
    return -1;
}

