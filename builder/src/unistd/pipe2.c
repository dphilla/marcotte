#include <unistd.h>

int pipe2(int pipefd[2], int flags)
{
    (void)flags;
    return pipe(pipefd);
}

