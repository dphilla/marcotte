#include <stdio.h>
#include <stdarg.h>   // for variadic
#include <string.h>   // maybe for vsnprintf, etc.

/*
 * Minimal 'printf': same as fprintf(stdout, ...).
 */

int printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    char buffer[512];
    int ret = vsnprintf(buffer, sizeof(buffer), format, ap);
    va_end(ap);

    // In a real environment, write buffer to stdout
    // For now, we do nothing or a debug stub
    return ret;
}
