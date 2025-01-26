/**
 * inet_netof.c
 *
 * Returns the "network portion" of an IPv4 address in old classful logic.
 * We'll do a minimal approach: just return the top 24 bits for class C, etc.
 */

#include <arpa/inet.h>
#include <stdint.h>

in_addr_t inet_netof(struct in_addr in)
{
    uint32_t addr = ntohl(in.s_addr);
    // If we do a simple class C approach, that's top 24 bits:
    return (addr >> 8);
}

