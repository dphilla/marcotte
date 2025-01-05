/**
 * htons.c
 *
 * Converts 16-bit host-order to network-order (big-endian).
 */
#include <stdint.h>

uint16_t htons(uint16_t hostshort)
{
#ifdef __BIG_ENDIAN__
    return hostshort;
#else
    /* or __builtin_bswap16 if your compiler supports it */
    return (uint16_t)(((hostshort & 0x00FFU) << 8) |
                      ((hostshort & 0xFF00U) >> 8));
#endif
}

