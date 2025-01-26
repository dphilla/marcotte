/**
 * bcmp.c
 *
 * Compares two memory blocks (s1, s2) of size n.
 * Returns 0 if they are identical, non-zero otherwise.
 */

#include <stddef.h>    // for size_t
#include <string.h>    // for memcmp

int bcmp(const void *s1, const void *s2, size_t n)
{
    // bcmp historically returns 0 if match, non-zero if differ.
    // memcmp returns 0 if match, non-zero negative/positive otherwise.
    // We only care about 0 vs non-zero, so:
    return memcmp(s1, s2, n) != 0;
}

