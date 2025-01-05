/**
 * freeaddrinfo.c
 */
#include <netdb.h>
#include "networking_syscalls.h"
#include "r.h"

void freeaddrinfo(struct addrinfo *res)
{
    // Possibly we do a "virtual" call to free the remote object.
    // Or do nothing if the host already freed it. Minimal stub:
    (void)res;
    return;
}

