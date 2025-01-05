/**
 * connect.c
 */
#include <sys/socket.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>

#include "bits/networking_syscalls.h"
#include "bits/r.h"

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    ArgDesc args[4];

    int32_t sysno = SYS_connect;
    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &sysno;

    args[1].arg_type   = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr   = (void*)&sockfd;

    args[2].arg_type   = ARGTYPE_PTR_IN;
    args[2].size_bytes = addrlen;
    args[2].data_ptr   = (void*)addr;

    args[3].arg_type   = ARGTYPE_SCALAR;
    args[3].size_bytes = sizeof(socklen_t);
    args[3].data_ptr   = (void*)&addrlen;

    return create_and_send_buffer_ext(4, args);
}

