/**
 * inet_aton.c
 *
 * Like inet_addr, but stores the result in *addr and returns nonzero on success.
 * 0 on failure.
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <stdint.h>

int inet_aton(const char *cp, struct in_addr *inp)
{
    // parse dotted decimal
    unsigned a,b,c,d;
    if (sscanf(cp, "%u.%u.%u.%u", &a, &b, &c, &d) != 4) {
        return 0;
    }
    if (a>255||b>255||c>255||d>255) {
        return 0;
    }
    uint32_t val = (a<<24)|(b<<16)|(c<<8)|d;
    inp->s_addr = htonl(val);
    return 1;
}

