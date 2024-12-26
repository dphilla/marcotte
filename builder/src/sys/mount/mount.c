#include <sys/mount.h>
#include <errno.h>

//TODO - some version of this will be possible in wasmvfs, in at worst some behavior-mimicking way
int mount(const char *source, const char *target, const char *filesystemtype,
          unsigned long mountflags, const void *data)
{
    (void)source; (void)target; (void)filesystemtype; (void)mountflags; (void)data;
    errno = ENOSYS;
    return -1;
}

