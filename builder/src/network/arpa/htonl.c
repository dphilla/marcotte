/**
 * htonl.c
 *
 * Converts 32-bit host-order to network-order (big-endian).
 */

#include <stdint.h>

uint32_t htonl(uint32_t hostlong)
{
#ifdef __BIG_ENDIAN__
    return hostlong;
#else
    /* A built-in could do this: __builtin_bswap32(hostlong). */
    return ((hostlong & 0x000000FFU) << 24) |
           ((hostlong & 0x0000FF00U) <<  8) |
           ((hostlong & 0x00FF0000U) >>  8) |
           ((hostlong & 0xFF000000U) >> 24);
#endif
}

