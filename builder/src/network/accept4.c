/**
 * accept4.c
 */
#include <sys/socket.h>
#include <stdint.h>
#include "bits/networking_syscalls.h"
#include "bits/r.h"

int accept4(int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags)
{
    ArgDesc args[5];

    int32_t sysno = SYS_accept4;
    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &sysno;

    args[1].arg_type   = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr   = (void*)&sockfd;

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

    args[4].arg_type   = ARGTYPE_SCALAR;
    args[4].size_bytes = 4;
    args[4].data_ptr   = (void*)&flags;

    return create_and_send_buffer_ext(5, args);
}

