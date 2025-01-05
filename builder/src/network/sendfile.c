/**
 * sendfile.c
 */
#include <sys/sendfile.h>
#include "networking_syscalls.h"
#include "r.h"

ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count)
{
    // The real kernel signature is:
    //    sendfile(out_fd, in_fd, off_t *offset, size_t count);
    // We'll pass them as 4 arguments plus the syscall #.
    ArgDesc args[4 + 1];
    int32_t sysno = SYS_sendfile;

    args[0].arg_type = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr = &sysno;

    args[1].arg_type = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr = &out_fd;

    args[2].arg_type = ARGTYPE_SCALAR;
    args[2].size_bytes = 4;
    args[2].data_ptr = &in_fd;

    // offset pointer is inout, if not null
    if (offset) {
        args[3].arg_type = ARGTYPE_PTR_INOUT;
        args[3].size_bytes = sizeof(off_t);
        args[3].data_ptr = offset;
    } else {
        args[3].arg_type = ARGTYPE_PTR_OUT;
        args[3].size_bytes = 0;
        args[3].data_ptr = NULL;
    }

    // count
    args[4].arg_type = ARGTYPE_SCALAR;
    args[4].size_bytes = sizeof(size_t);
    args[4].data_ptr = &count;

    return (ssize_t) create_and_send_buffer_ext(5, args);
}

