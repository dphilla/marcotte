#include <unistd.h>
int sync(void)
{
    /* no-op in in-memory VFS. */
    return 0;
}

