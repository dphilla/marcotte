/**
 * inet_ntoa.c
 *
 * Takes a struct in_addr (4-byte in network order),
 * returns dotted-decimal string in a static buffer.
 */

#include <arpa/inet.h>   // for struct in_addr
#include <stdio.h>       // for snprintf
#include <stdint.h>

char *inet_ntoa(struct in_addr in)
{
    // Typically a static buffer is used.
    // We'll do that or store it in thread-local if you prefer. For demonstration:
    static char buffer[16];

    uint32_t addr = ntohl(in.s_addr);
    unsigned a = (addr >> 24) & 0xFF;
    unsigned b = (addr >> 16) & 0xFF;
    unsigned c = (addr >> 8)  & 0xFF;
    unsigned d = addr & 0xFF;

    snprintf(buffer, sizeof(buffer), "%u.%u.%u.%u", a,b,c,d);
    return buffer;
}

