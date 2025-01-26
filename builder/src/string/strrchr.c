/**
 * strrchr.c
 *
 * Returns a pointer to the last occurrence of character c
 * in the C-string s, or NULL if not found.
 * If c == '\0', returns pointer to the terminating null character.
 */

#include <stddef.h> // for NULL

char *strrchr(const char *s, int c)
{
    // Convert c to unsigned char for consistency
    unsigned char ch = (unsigned char)c;

    const char *last = NULL;

    // Walk to the end
    while (*s) {
        if ((unsigned char)*s == ch) {
            last = s; // track latest occurrence
        }
        s++;
    }
    // If searching for '\0', then return pointer to terminator
    if (ch == '\0') {
        return (char *)s;
    }

    return (char *)last; // cast away const
}

