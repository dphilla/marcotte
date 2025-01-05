/**
 * strcasecmp.c
 *
 * Case-insensitive string compare. Returns 0 if match,
 * <0 / >0 if s1 < s2 or s1 > s2 ignoring case.
 */

#include <ctype.h>
#include <string.h>

int strcasecmp(const char *s1, const char *s2)
{
    // We'll implement a simple loop:
    unsigned char c1, c2;
    for (;; s1++, s2++) {
        c1 = (unsigned char) *s1;
        c2 = (unsigned char) *s2;
        // tolower
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

        if (c1 != c2 || c1 == '\0') {
            return (int)c1 - (int)c2;
        }
    }
}

