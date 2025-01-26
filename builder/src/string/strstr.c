// builder/src/string/string_extras.c

#include <string.h>  // to match function prototypes

/*
 * A simple implementation of strstr, which finds the first occurrence
 * of `needle` in `haystack`.
 */
char *strstr(const char *haystack, const char *needle)
{
    if (!haystack || !needle) return NULL;
    if (*needle == '\0') {
        // Per POSIX, if needle == "", return (char*)haystack
        return (char *)haystack;
    }

    // Naive substring search
    for (; *haystack; haystack++) {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && (*h == *n)) {
            h++;
            n++;
        }
        if (*n == '\0') {
            // Found full match
            return (char *)haystack;
        }
    }
    return NULL;
}

