/**
 * bzero.c
 *
 * Sets n bytes of s to zero.
 */

#include <stddef.h>   // for size_t
#include <string.h>   // for memset

void bzero(void *s, size_t n)
{
    memset(s, 0, n);
}

