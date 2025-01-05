/**
 * index.c
 *
 * Returns a pointer to the first occurrence of character c in string s,
 * or NULL if c not found.
 * This is an old BSD function, basically the same as strchr().
 */

#include <string.h>  // for strchr

char *index(const char *s, int c)
{
    return strchr(s, c);
}

