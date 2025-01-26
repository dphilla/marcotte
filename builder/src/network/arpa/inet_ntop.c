/**
 * inet_ntop.c
 *
 * Converts binary IP to string. We only do AF_INET for demonstration.
 * Returns 'dst' on success, or NULL on fail.
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size)
{
    if (af == AF_INET) {
        if (size < 16) { // not enough space for "255.255.255.255\0"
            return NULL;
        }
        uint32_t val;
        memcpy(&val, src, 4);
        val = ntohl(val);
        unsigned a = (val>>24)&0xFF, b=(val>>16)&0xFF, c=(val>>8)&0xFF, d=(val)&0xFF;
        snprintf(dst, size, "%u.%u.%u.%u", a,b,c,d);
        return dst;
    } else if (af == AF_INET6) {
        // Not implemented fully
        return NULL;
    }
    return NULL;
}

