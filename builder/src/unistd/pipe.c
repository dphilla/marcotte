#include <unistd.h>
#include <errno.h>

/* TODO - when Proc is extracted and PKC exists - this will be done via module imports/exports, like other
 * process-related things */
int pipe(int pipefd[2])
{
    errno = ENOSYS;
    return -1;
}

