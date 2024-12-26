#include <sys/mman.h>
#include <errno.h>

//TODO - this will be supported once PKC and Proc are extracted, in some way
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    (void)addr; (void)length; (void)prot; (void)flags; (void)fd; (void)offset;
    errno = ENOSYS;
    return MAP_FAILED;
}

