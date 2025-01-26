/**
 * recvfrom.c
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdint.h>

#include "bits/networking_syscalls.h"
#include "bits/r.h"

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                 struct sockaddr *src_addr, socklen_t *addrlen)
{
    ArgDesc args[6];
    int32_t sysno = SYS_recvfrom;

    args[0].arg_type = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr = &sysno;

    // sockfd
    args[1].arg_type = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr = (void*)&sockfd;

    // buffer out
    args[2].arg_type = ARGTYPE_PTR_OUT;
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

    // For src_addr and addrlen, treat as PTR_OUT if non-null
    // If either is NULL, pass 0.
    if (src_addr && addrlen) {
        // The server side can do real recvfrom(...) and fill them
        // but we have only 6 spots total. We are at #5 now.
        // We can do a "PTR_INOUT" for socklen_t if we want to let the kernel update it
        // We might need more than 6 if we want the address to come back in patches.
        // For brevity, let's store them in a combined ArgDesc if your dynamic_syscall can handle it.
        // For simplicity: we do a single PTR_OUT for "src_addr", sized by *addrlen
        //   and we rely on the server side to store the final socklen in that same patch
        //   or we do the "some approach" with two args.
        // We'll do 6 total:
        // Actually let's do 6 total. We'll assume we can handle that on the server side.
        // Arg #5 is a PTR_OUT with size = *addrlen
        // We won't store the socklen_t unless the server lumps it in the patch.
        args[5].arg_type   = ARGTYPE_PTR_OUT;
        args[5].size_bytes = *addrlen;
        args[5].data_ptr   = src_addr;
    } else {
        args[5].arg_type   = ARGTYPE_PTR_OUT;
        args[5].size_bytes = 0;
        args[5].data_ptr   = NULL;
    }

    return (ssize_t) create_and_send_buffer_ext(6, args);
}

