/**
 * bcopy.c
 *
 * Copies n bytes from src to dest, handling overlap.
 * Historically the BSD function bcopy just does overlap-safe copying,
 * which is effectively memmove.
 */

#include <stddef.h>   // for size_t
#include <string.h>   // for memmove

void bcopy(const void *src, void *dest, size_t n)
{
    memmove(dest, src, n);
}

