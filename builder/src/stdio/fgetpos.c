#include <stdio.h>

int fgetpos(FILE *stream, fpos_t *pos)
{
    if (!stream || !pos) return -1;
    long p = ftell(stream);   // ftell() returns a long
    if (p < 0) return -1;

    // Instead of casting p to the entire union, just store it in __lldata
    pos->__lldata = (long long)p;
    return 0;
}

