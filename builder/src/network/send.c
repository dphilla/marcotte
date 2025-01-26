/**
 * send.c
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdint.h>

#include "bits/networking_syscalls.h"
#include "bits/r.h"

ssize_t send(int sockfd, const void *buf, size_t len, int flags)
{
    ArgDesc args[5];
    int32_t sysno = SYS_sendto; // send(...) is typically a wrapper around sendto with no dest

    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &sysno;

    args[1].arg_type   = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr   = (void*)&sockfd;

    // data pointer
    args[2].arg_type   = ARGTYPE_PTR_IN;
    args[2].size_bytes = len;
    args[2].data_ptr   = (void*)buf;

    // len
    args[3].arg_type   = ARGTYPE_SCALAR;
    args[3].size_bytes = sizeof(size_t);
    args[3].data_ptr   = (void*)&len;

    // flags
    args[4].arg_type   = ARGTYPE_SCALAR;
    args[4].size_bytes = 4;
    args[4].data_ptr   = (void*)&flags;

    return (ssize_t) create_and_send_buffer_ext(5, args);
}

