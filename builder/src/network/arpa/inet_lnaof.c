/**
 * inet_lnaof.c
 *
 * Returns the "local network address" portion (host part) of an IPv4.
 * Implementation is somewhat old-fashioned. We'll do a minimal approach:
 *
 * Typically for classful addressing (class A, B, C). We'll just do a "lowest 24 bits."
 */

//TODO
#include <arpa/inet.h>
#include <stdint.h>

in_addr_t inet_lnaof(struct in_addr in)
{
    uint32_t addr = ntohl(in.s_addr);
    // Let's pretend we only do class C. That means the last 8 bits are host.
    // But historically it might check the first bits. We'll do a simple approach:
    // return low 8 bits:
    return addr & 0xFF;
}

