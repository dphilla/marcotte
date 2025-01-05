/**
 * sendmsg.c
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdint.h>
#include "bits/networking_syscalls.h"
#include "bits/r.h"

ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags)
{
    ArgDesc args[4];
    int32_t sysno = SYS_sendmsg;

    args[0].arg_type = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr = &sysno;

    args[1].arg_type = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr = &sockfd;

    args[2].arg_type = ARGTYPE_PTR_IN;
    args[2].size_bytes = sizeof(struct msghdr);
    args[2].data_ptr = (void*)msg;

    args[3].arg_type = ARGTYPE_SCALAR;
    args[3].size_bytes = 4;
    args[3].data_ptr = &flags;

    return (ssize_t)create_and_send_buffer_ext(4, args);
}

