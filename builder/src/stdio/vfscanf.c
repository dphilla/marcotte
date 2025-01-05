/**
 * vfscanf.c
 *
 * The variadic version of fscanf, receiving a va_list.
 * Minimal stub returning 0.
 */

#include <stdio.h>
#include <stdarg.h>

int vfscanf(FILE *stream, const char *format, __isoc_va_list ap)
{
  //TODO
    (void)stream;
    (void)format;
    (void)ap;
    return 0;
}

