#include <unistd.h>

int lchown(const char *path, uid_t owner, gid_t group)
{
    /* same as chown for a typical in-memory VFS that doesn't treat symlinks differently. */
    return chown(path, owner, group);
}

