/**
 * getsockopt.c
 */
#include <sys/socket.h>
#include <stdint.h>
#include "bits/networking_syscalls.h"
#include "bits/r.h"

int getsockopt(int sockfd, int level, int optname,
               void *optval, socklen_t *optlen)
{
    ArgDesc args[5];
    int32_t sysno = SYS_getsockopt;

    args[0].arg_type = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr = &sysno;

    args[1].arg_type = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr = &sockfd;

    args[2].arg_type = ARGTYPE_SCALAR;
    args[2].size_bytes = 4;
    args[2].data_ptr = &level;

    args[3].arg_type = ARGTYPE_SCALAR;
    args[3].size_bytes = 4;
    args[3].data_ptr = &optname;

    //TODO
    // For demonstration, we combine *optval + *optlen in a single argument or do partial.
    // Real code might do two arguments (the pointer + the pointer to length).
    // We'll do a single PTR_INOUT if we assume we can figure out the length on the server side:
    if (optval && optlen) {
        args[4].arg_type   = ARGTYPE_PTR_INOUT;
        args[4].size_bytes = *optlen;
        args[4].data_ptr   = optval;
    } else {
        args[4].arg_type   = ARGTYPE_PTR_OUT;
        args[4].size_bytes = 0;
        args[4].data_ptr   = NULL;
    }

    return create_and_send_buffer_ext(5, args);
}

