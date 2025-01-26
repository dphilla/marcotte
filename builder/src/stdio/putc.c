/**
 * putc.c
 *
 * A thin wrapper that calls fputc().
 */

#include <stdio.h>

int putc(int c, FILE *stream)
{
    return fputc(c, stream);
}

