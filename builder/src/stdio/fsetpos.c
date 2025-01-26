#include <stdio.h>

int fsetpos(FILE *stream, const fpos_t *pos)
{
    if (!stream || !pos) return -1;

    // Instead of casting *pos to a long, we get the offset from __lldata
    long offset = (long)pos->__lldata;
    return fseek(stream, offset, 0 /*SEEK_SET*/);
}

