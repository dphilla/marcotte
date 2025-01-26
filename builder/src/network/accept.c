/**
 * accept.c
 *
 * Note: If addr is not NULL, the kernel writes back the remote address.
 * We'll mark it PTR_OUT to patch it back. If addrlen is also not NULL, we also do SCALAR in/out
 * or handle as PTR_INOUT if we want the kernel to update it.
 */
#include <sys/socket.h>
#include <stdint.h>
#include <string.h>
#include "bits/networking_syscalls.h"
#include "bits/r.h"

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    ArgDesc args[4];

    int32_t sysno = SYS_accept;
    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &sysno;

    args[1].arg_type   = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr   = (void*)&sockfd;

    if (addr && addrlen) {
        // We'll do PTR_OUT for the address, sized by *addrlen
        args[2].arg_type   = ARGTYPE_PTR_OUT;
        args[2].size_bytes = *addrlen;
        args[2].data_ptr   = addr;

        // We also pass in the socklen pointer as PTR_INOUT, so kernel can update it
        // However, the actual kernel signature is just two arguments,
        // but for proxy we treat this carefully so the server side can do the real accept.
        // We'll store the size in a 4-byte int if your socklen_t is 4 bytes
        // (commonly socklen_t is 4 on many platforms).
        args[3].arg_type   = ARGTYPE_PTR_INOUT;
        args[3].size_bytes = sizeof(socklen_t);
        args[3].data_ptr   = addrlen;

        return create_and_send_buffer_ext(4, args);
    } else {
        // If user passed NULL, we can just do 2 or 3 arguments
        // For simplicity, pass zero-size pointer
        args[2].arg_type   = ARGTYPE_PTR_OUT;
        args[2].size_bytes = 0;
        args[2].data_ptr   = NULL;

        args[3].arg_type   = ARGTYPE_PTR_OUT;
        args[3].size_bytes = 0;
        args[3].data_ptr   = NULL;

        return create_and_send_buffer_ext(4, args);
    }
}

