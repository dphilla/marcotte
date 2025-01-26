#include <stdio.h>

int pclose(FILE *stream)
{
    /* If popen was not truly implemented, pclose can do nothing. */
    return fclose(stream);
}

