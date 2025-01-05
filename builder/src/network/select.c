/**
 * select.c
 */
#include <sys/select.h>
#include "networking_syscalls.h"
#include "r.h"

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
           struct timeval *timeout)
{
    ArgDesc args[6];
    int32_t sysno = SYS_select; // #23

    args[0].arg_type = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr = &sysno;

    args[1].arg_type = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr = &nfds;

    args[2].arg_type = readfds ? ARGTYPE_PTR_INOUT : ARGTYPE_PTR_OUT;
    args[2].size_bytes = readfds ? sizeof(fd_set) : 0; // oversimplified
    args[2].data_ptr = readfds;

    args[3].arg_type = writefds ? ARGTYPE_PTR_INOUT : ARGTYPE_PTR_OUT;
    args[3].size_bytes = writefds ? sizeof(fd_set) : 0;
    args[3].data_ptr = writefds;

    args[4].arg_type = exceptfds ? ARGTYPE_PTR_INOUT : ARGTYPE_PTR_OUT;
    args[4].size_bytes = exceptfds ? sizeof(fd_set) : 0;
    args[4].data_ptr = exceptfds;

    args[5].arg_type = timeout ? ARGTYPE_PTR_INOUT : ARGTYPE_PTR_OUT;
    args[5].size_bytes = timeout ? sizeof(struct timeval) : 0;
    args[5].data_ptr = timeout;

    return create_and_send_buffer_ext(6, args);
}

