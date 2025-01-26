#include <dirent.h>
#include <unistd.h>   /* lseek() */

void rewinddir(DIR *dirp)
{
    if (!dirp) return;
    lseek(dirp->fd, 0, SEEK_SET);
    dirp->buf_pos = 0;
    dirp->buf_end = 0;
}

