#include <dirent.h>
#include <stdlib.h>     /* free() */
#include <unistd.h>     /* close() */

int closedir(DIR *dirp)
{
    if (!dirp) return -1;
    close(dirp->fd);  /* release the underlying directory FD */
    free(dirp);
    return 0;
}

