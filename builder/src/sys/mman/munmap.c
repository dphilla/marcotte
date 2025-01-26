#include <sys/mman.h>
#include <errno.h>

int munmap(void *addr, size_t length)
{
    (void)addr; (void)length;
    errno = ENOSYS;
    return -1;
}

