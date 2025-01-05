/**
 * rindex.c
 *
 * Returns a pointer to the last occurrence of character c in string s,
 * or NULL if not found.
 * This is an old BSD function, basically the same as strrchr().
 */

#include <string.h>  // for strrchr

char *rindex(const char *s, int c)
{
    return strrchr(s, c);
}

