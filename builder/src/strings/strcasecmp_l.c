/**
 * strcasecmp_l.c
 *
 * Case-insensitive compare, ignoring the locale param (for now).
 * If you want real locale logic, you'd do more than just call strcasecmp.
 */

#include <strings.h>   // for strcasecmp
#include <locale.h>

int strcasecmp_l(const char *s1, const char *s2, locale_t loc)
{
    // Currently ignoring 'loc' (we're in a minimal environment).
    // Just call strcasecmp.
    (void)loc;
    return strcasecmp(s1, s2);
}

