/**
 * sendto.c
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdint.h>

#include "bits/networking_syscalls.h"
#include "bits/r.h"

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen)
{
    ArgDesc args[6];
    int32_t sysno = SYS_sendto;

    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &sysno;

    args[1].arg_type   = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr   = (void*)&sockfd;

    args[2].arg_type   = ARGTYPE_PTR_IN;
    args[2].size_bytes = len;
    args[2].data_ptr   = (void*)buf;

    args[3].arg_type   = ARGTYPE_SCALAR;
    args[3].size_bytes = sizeof(size_t);
    args[3].data_ptr   = (void*)&len;

    args[4].arg_type   = ARGTYPE_SCALAR;
    args[4].size_bytes = 4;
    args[4].data_ptr   = (void*)&flags;

    if (dest_addr && addrlen > 0) {
        args[5].arg_type   = ARGTYPE_PTR_IN;
        args[5].size_bytes = addrlen;
        args[5].data_ptr   = (void*)dest_addr;
    } else {
        args[5].arg_type   = ARGTYPE_PTR_IN;
        args[5].size_bytes = 0;
        args[5].data_ptr   = NULL;
    }

    return (ssize_t) create_and_send_buffer_ext(6, args);
}

