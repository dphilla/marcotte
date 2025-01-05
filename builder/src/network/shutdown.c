/**
 * shutdown.c
 */
#include <sys/socket.h>
#include "bits/networking_syscalls.h"
#include "bits/r.h"

int shutdown(int sockfd, int how)
{
    ArgDesc args[3];
    int32_t sysno = SYS_shutdown;

    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &sysno;

    args[1].arg_type   = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr   = &sockfd;

    args[2].arg_type   = ARGTYPE_SCALAR;
    args[2].size_bytes = 4;
    args[2].data_ptr   = &how;

    return create_and_send_buffer_ext(3, args);
}

