/**
 * inet_addr.c
 *
 * Converts an IPv4 dotted-decimal string to a 32-bit binary address
 * in network byte order. Returns INADDR_NONE on error (which is 0xFFFFFFFF).
 *
 * Because this function is old / not recommended, we do a minimal parse.
 */

#include <stdint.h>
#include <stdio.h>   // for sscanf
#include <arpa/inet.h> // for in_addr_t

in_addr_t inet_addr(const char *cp)
{
    // We'll parse dotted-decimal: a.b.c.d
    unsigned a, b, c, d;
    int matched = sscanf(cp, "%u.%u.%u.%u", &a, &b, &c, &d);
    if (matched != 4 || a > 255 || b > 255 || c > 255 || d > 255) {
        // return INADDR_NONE, typically 0xFFFFFFFF
        return 0xFFFFFFFFU;
    }
    // combine
    uint32_t addr = (a << 24) | (b << 16) | (c << 8) | d;
    return htonl(addr);
}

