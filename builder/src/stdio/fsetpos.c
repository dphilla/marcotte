#include <stdio.h>

int fsetpos(FILE *stream, const fpos_t *pos)
{
    if (!stream || !pos) return -1;
    return fseek(stream, (long)*pos, 0 /*SEEK_SET*/);
}

