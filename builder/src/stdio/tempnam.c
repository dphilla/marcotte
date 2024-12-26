#include <stdio.h>
#include <stdlib.h> /* malloc */
#include <string.h>

char *tempnam(const char *dir, const char *pfx)
{
    /* naive approach: combine dir, pfx, random suffix */
    static unsigned counter = 0;
    if (!dir) dir = "/tmp";
    if (!pfx) pfx = "tmp";

    char *result = malloc(256);
    if (!result) return NULL;
    snprintf(result, 256, "%s/%s_%u", dir, pfx, ++counter);
    return result;
}

