/**
 * getsockname.c
 */
#include <sys/socket.h>
#include <stdint.h>
#include "bits/networking_syscalls.h"
#include "bits/r.h"

int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    ArgDesc args[4];
    int32_t sysno = SYS_getsockname;

    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &sysno;

    args[1].arg_type   = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr   = &sockfd;

    if (addr && addrlen) {
        args[2].arg_type   = ARGTYPE_PTR_OUT;
        args[2].size_bytes = *addrlen;
        args[2].data_ptr   = addr;

        args[3].arg_type   = ARGTYPE_PTR_INOUT;
        args[3].size_bytes = sizeof(socklen_t);
        args[3].data_ptr   = addrlen;
    } else {
        args[2].arg_type   = ARGTYPE_PTR_OUT;
        args[2].size_bytes = 0;
        args[2].data_ptr   = NULL;

        args[3].arg_type   = ARGTYPE_PTR_OUT;
        args[3].size_bytes = 0;
        args[3].data_ptr   = NULL;
    }

    return create_and_send_buffer_ext(4, args);
}

