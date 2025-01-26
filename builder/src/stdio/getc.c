/**
 * getc.c
 *
 * A thin wrapper that calls fgetc().
 */

#include <stdio.h>

int getc(FILE *stream)
{
    return fgetc(stream);
}

