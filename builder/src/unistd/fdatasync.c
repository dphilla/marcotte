#include <unistd.h>

//TODO - huge via Wasm-vfs to host, and via plugins, directly to blocks, etc.
int fdatasync(int fd)
{
    /* no real disk, no-op. */
    (void)fd;
    return 0;
}

