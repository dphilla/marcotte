/**
 * ntohl.c
 *
 * Converts 32-bit network-order (big-endian) to host-order.
 * On little-endian, we swap. On big-endian, do nothing.
 */

#include <stdint.h>

uint32_t ntohl(uint32_t netlong)
{
    /* same logic as htonl, reversed.  But htonl == ntohl on most implementations. */
#ifdef __BIG_ENDIAN__
    return netlong;
#else
    return ((netlong & 0x000000FFU) << 24) |
           ((netlong & 0x0000FF00U) <<  8) |
           ((netlong & 0x00FF0000U) >>  8) |
           ((netlong & 0xFF000000U) >> 24);
#endif
}

