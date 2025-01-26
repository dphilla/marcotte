/**
 * ioctl.c
 */
#include <sys/ioctl.h> // for prototype
#include "bits/networking_syscalls.h"
#include "bits/r.h"

int ioctl(int fd, int request, ...)
{
    // parse varargs if needed
    ArgDesc args[3];
    int32_t fake_sysno = 999; // or real

    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &fake_sysno;

    args[1].arg_type   = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr   = &fd;

    args[2].arg_type   = ARGTYPE_SCALAR;
    args[2].size_bytes = 4;
    args[2].data_ptr   = &request;

    return create_and_send_buffer_ext(3, args);
}

