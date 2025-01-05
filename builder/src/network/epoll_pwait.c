/**
 * epoll_pwait.c
 */
#include <sys/epoll.h>   // for struct epoll_event
#include <signal.h>      // for sigset_t
#include <stdint.h>
#include "bits/r.h"      // your ArgDesc, etc.
#include "bits/networking_syscalls.h"

int epoll_pwait(int fd, struct epoll_event *events, int maxevents,
                int timeout, const sigset_t *sigmask)
{
    // Example ArgDesc approach:
    ArgDesc args[6];
    // Suppose your SYS_epoll_pwait is #281 or something. Use real number or “fake” if the kernel is 4-arg.
    int32_t sysno = 281; // or whatever your networking_syscalls.h says

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

    // The sigmask is a pointer to a sigset_t
    // If you want to handle patching for signals, do so. For simplicity:
    if (sigmask) {
        args[5].arg_type   = ARGTYPE_PTR_IN;
        args[5].size_bytes = sizeof(sigset_t);
        args[5].data_ptr   = (void*)sigmask;
    } else {
        args[5].arg_type   = ARGTYPE_PTR_IN;
        args[5].size_bytes = 0;
        args[5].data_ptr   = NULL;
    }

    return create_and_send_buffer_ext(6, args);
}

