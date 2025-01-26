/**
 * fscanf.c
 *
 * Minimal stub that might call vfscanf().
 * We'll do a stub returning 0.
 */

#include <stdio.h>
#include <stdarg.h>

int fscanf(FILE *stream, const char *format, ...)
  //TODO - implement
{
    (void)stream;
    (void)format;
    return 0;
}

