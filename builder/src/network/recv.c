/**
 * recv.c
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdint.h>
#include <string.h>

#include "bits/networking_syscalls.h"
#include "bits/r.h"

ssize_t recv(int sockfd, void *buf, size_t len, int flags)
{
    ArgDesc args[4 + 1]; // we have 5 total: syscall, sockfd, PTR_OUT, len, flags
    int32_t sysno = SYS_recvfrom; // Actually, 'recv' is typically a library wrapper for recvfrom(..., NULL, 0)
                                  // but let's treat it as SYS_recvfrom with a zero address

    args[0].arg_type = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr = &sysno;

    // sockfd
    args[1].arg_type = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr = (void*)&sockfd;

    // buffer
    args[2].arg_type = ARGTYPE_PTR_OUT;  // kernel writes data
    args[2].size_bytes = len;
    args[2].data_ptr = buf;

    // len
    args[3].arg_type = ARGTYPE_SCALAR;
    args[3].size_bytes = sizeof(size_t);
    args[3].data_ptr = (void*)&len;

    // flags
    args[4].arg_type = ARGTYPE_SCALAR;
    args[4].size_bytes = 4;
    args[4].data_ptr = (void*)&flags;

    return (ssize_t) create_and_send_buffer_ext(5, args);
}

