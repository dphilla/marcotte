/**
 * ntohs.c
 *
 * Converts 16-bit network-order to host-order.
 */

#include <stdint.h>

uint16_t ntohs(uint16_t netshort)
{
#ifdef __BIG_ENDIAN__
    return netshort;
#else
    return (uint16_t)(((netshort & 0x00FFU) << 8) |
                      ((netshort & 0xFF00U) >> 8));
#endif
}
