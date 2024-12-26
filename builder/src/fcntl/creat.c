#include <fcntl.h>
int creat(const char *pathname, mode_t mode)
{
    /* creat is open with O_WRONLY|O_CREAT|O_TRUNC */
    return open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
}

