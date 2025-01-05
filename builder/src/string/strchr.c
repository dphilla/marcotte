/**
 * strchr.c
 *
 * Returns a pointer to the first occurrence of character c
 * in the C-string s, or NULL if not found.
 * If c == '\0', returns pointer to the terminating null character.
 */

#include <stddef.h> // for NULL

char *strchr(const char *s, int c)
{
    // Convert c to unsigned char if you want consistent behavior
    unsigned char ch = (unsigned char)c;

    while (*s) {
        if ((unsigned char)*s == ch) {
            return (char *)s; // cast away const
        }
        s++;
    }
    // If c is '\0', return pointer to the terminator
    if (ch == '\0') {
        return (char *)s;
    }
    return NULL;
}

