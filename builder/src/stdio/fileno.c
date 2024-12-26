#include <stdio.h>

int fileno(FILE *stream)
{
    if (!stream) return -1;
    return stream->fd;
}

