/**
 * epoll_wait.c
 */
#include <sys/epoll.h>   // struct epoll_event
#include <stdint.h>
#include "bits/networking_syscalls.h"
#include "bits/r.h"

int epoll_wait(int fd, struct epoll_event *events, int maxevents, int timeout)
{
    ArgDesc args[5];
    int32_t sysno = 232; // e.g. SYS_epoll_wait = 232 on x86_64

    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &sysno;

    args[1].arg_type   = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr   = &fd;

    args[2].arg_type   = ARGTYPE_PTR_INOUT;
    args[2].size_bytes = maxevents * sizeof(struct epoll_event);
    args[2].data_ptr   = events;

    args[3].arg_type   = ARGTYPE_SCALAR;
    args[3].size_bytes = 4;
    args[3].data_ptr   = &maxevents;

    args[4].arg_type   = ARGTYPE_SCALAR;
    args[4].size_bytes = 4;
    args[4].data_ptr   = &timeout;

    return create_and_send_buffer_ext(5, args);
}

