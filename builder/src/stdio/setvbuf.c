#include <stdio.h>

int setvbuf(FILE *stream, char *buf, int mode, size_t size)
{
    /* No real buffering in this minimal example. */
    (void)stream; (void)buf; (void)mode; (void)size;
    return 0;
}

