#include <stdio.h>

int fgetpos(FILE *stream, fpos_t *pos)
{
    if (!stream || !pos) return -1;
    long p = ftell(stream);
    if (p < 0) return -1;
    *pos = (fpos_t)p;
    return 0;
}

