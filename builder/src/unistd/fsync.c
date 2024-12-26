#include <unistd.h>

//TODO - huge via Wasm-vfs to host, and via plugins, directly to blocks, etc.
int fsync(int fd)
{
    (void)fd;
    return 0; /* no-op */
}

