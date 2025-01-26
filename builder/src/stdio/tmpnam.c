#include <stdio.h>
#include <string.h>

char *tmpnam(char *s)
{
    static char internal[64];
    static unsigned counter = 0;

    if (!s) s = internal;
    snprintf(s, 64, "/tmp/tmp_%u", ++counter);
    return s;
}

