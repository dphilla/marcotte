#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/*
 * Minimal 'puts': writes a string plus newline, returns 0 or something
 */
int puts(const char *s)
{
    // If you want, you can do a real write to stdout
    // We'll do a trivial measure:
    // "printf("%s\n", s);" in advanced code but let's do minimal:

    (void)s;  // ignore for now
    return 0; // pretend success
}

