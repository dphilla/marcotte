#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *freopen(const char *filename, const char *mode, FILE *stream)
{
    if (stream) fclose(stream);
    return fopen(filename, mode);
}

