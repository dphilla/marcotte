/**
 * poll.c
 */
#include <poll.h>
#include "bits/networking_syscalls.h"
#include "bits/r.h"

int poll(struct pollfd *fds, nfds_t nfds, int timeout)
{
    ArgDesc args[4];
    int32_t sysno = SYS_poll;  // #7
    args[0].arg_type = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr = &sysno;

    args[1].arg_type = ARGTYPE_PTR_INOUT;
    args[1].size_bytes = sizeof(struct pollfd) * nfds;
    args[1].data_ptr = fds;

    args[2].arg_type = ARGTYPE_SCALAR;
    args[2].size_bytes = sizeof(nfds_t);
    args[2].data_ptr = &nfds;

    args[3].arg_type = ARGTYPE_SCALAR;
    args[3].size_bytes = 4; // assume int
    args[3].data_ptr = &timeout;

    return create_and_send_buffer_ext(4, args);
}

