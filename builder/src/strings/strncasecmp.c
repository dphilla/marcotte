/**
 * strncasecmp.c
 *
 * Case-insensitive compare of up to n chars. Returns 0 if match,
 * <0 or >0 if differ ignoring case.
 */

#include <ctype.h>
#include <string.h>
#include <stddef.h>

int strncasecmp(const char *s1, const char *s2, size_t n)
{
    unsigned char c1, c2;
    while (n--) {
        c1 = (unsigned char)*s1++;
        c2 = (unsigned char)*s2++;
        // tolower
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

        if (c1 != c2) {
            return (int)c1 - (int)c2;
        }
        if (c1 == '\0') {
            break;
        }
    }
    return 0;
}

