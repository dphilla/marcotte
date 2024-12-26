#include <unistd.h>

int renameat2(int olddirfd, const char *oldpath, int newdirfd,
              const char *newpath, unsigned int flags)
{
    /* ignoring flags, just rename. */
    return renameat(olddirfd, oldpath, newdirfd, newpath);
}

