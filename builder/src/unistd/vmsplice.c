#include <unistd.h>
#include <errno.h>

ssize_t vmsplice(int fd, const struct iovec *iov, size_t nr_segs, unsigned int flags)
{
    (void)fd; (void)iov; (void)nr_segs; (void)flags;
    errno = ENOSYS;
    return -1;
}

