/**
 * inet_network.c
 *
 * Historically: converts an IPv4 address with optional / bits into
 * a network #. Some implementations treat it differently. We'll do
 * a minimal approach: parse dotted decimal and return the hostlong portion.
 *
 * Return value in host order or net order is historically inconsistent.
 * We'll do it in host order (some BSD do that).
 */

#include <stdint.h>
#include <stdio.h>
#include <arpa/inet.h> // for in_addr_t

in_addr_t inet_network(const char *cp)
{
    // minimal parse, ignoring optional /bits:
    unsigned a, b, c, d;
    if (sscanf(cp, "%u.%u.%u.%u", &a, &b, &c, &d) != 4) {
        return (in_addr_t)-1;  // e.g. 0xFFFFFFFF
    }
    if (a>255 || b>255 || c>255 || d>255) {
        return (in_addr_t)-1;
    }
    // combine in host order
    return (a << 24) | (b << 16) | (c << 8) | d;
}

