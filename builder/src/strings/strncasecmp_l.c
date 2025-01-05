/**
 * strncasecmp_l.c
 *
 * Case-insensitive compare of up to n chars, ignoring locale param.
 */

#include <strings.h>   // for strncasecmp
#include <locale.h>
#include <stddef.h>

int strncasecmp_l(const char *s1, const char *s2, size_t n, locale_t loc)
{
    (void)loc; // ignore
    return strncasecmp(s1, s2, n);
}

