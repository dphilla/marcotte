/**
 * epoll_create.c
 */
#include <sys/epoll.h>
#include "bits/networking_syscalls.h"
#include "bits/r.h"

int epoll_create1(int size)
{
    ArgDesc args[2];
    int32_t sysno = SYS_epoll_create; // #213

    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &sysno;

    args[1].arg_type   = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr   = &size;

    return create_and_send_buffer_ext(2, args);
}

