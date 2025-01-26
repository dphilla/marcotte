/**
 * inet_makeaddr.c
 *
 * Combines 'net' and 'host' parts into a single IPv4 address.
 * Typically net is the network #, host is the local part.
 */

//TODO - verify

#include <arpa/inet.h>
#include <stdint.h>

struct in_addr inet_makeaddr(in_addr_t net, in_addr_t lna)
{
    // historically: net is high bits, lna is low bits
    // We'll combine them in a simplistic way.
    // e.g. net<<8 | lna, etc.
    // We'll guess net is in host order, same with lna.
    // Then produce s_addr in network order.

    uint32_t combined = ((net & 0xFF)<<24) | (lna & 0xFFFFFF);
    struct in_addr addr;
    addr.s_addr = htonl(combined);
    return addr;
}

