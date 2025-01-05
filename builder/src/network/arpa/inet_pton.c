/**
 * inet_pton.c
 *
 * Converts an IP string (AF_INET or AF_INET6) into binary form.
 * We only do AF_INET here for demonstration.
 * Returns 1 on success, 0 if invalid, -1 on some error.
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int inet_pton(int af, const char *src, void *dst)
{
    if (af == AF_INET) {
        // parse dotted decimal
        unsigned a,b,c,d;
        if (sscanf(src, "%u.%u.%u.%u", &a, &b, &c, &d) != 4) {
            return 0; // invalid format
        }
        if (a>255 || b>255 || c>255 || d>255) return 0;
        uint32_t val = (a<<24)|(b<<16)|(c<<8)|d;
        val = htonl(val);
        memcpy(dst, &val, 4);
        return 1;
    } else if (af == AF_INET6) {
        // Not fully implemented. Minimal approach or return 0
        return 0;
    }
    return -1; // unsupported family
}

