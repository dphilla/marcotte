/**
 * ioctl.c
 */
#include <sys/ioctl.h>
#include "networking_syscalls.h"
#include "r.h"

int ioctl(int fd, unsigned long request, ...)
{
  //TODO
    // Typically a variadic function. We'll do a simplified approach for one pointer arg:
    // real code might parse the varargs.

    void *argp = NULL;
    // parse varargs if you have it
    // or we keep it 0 for demonstration

    ArgDesc args[3];
    int32_t fake_sysno = 999993;

    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &fake_sysno;

    args[1].arg_type   = ARGTYPE_SCALAR;
    args[1].size_bytes = sizeof(int);
    args[1].data_ptr   = &fd;

    args[2].arg_type   = ARGTYPE_SCALAR;
    args[2].size_bytes = sizeof(unsigned long);
    args[2].data_ptr   = &request;

    return create_and_send_buffer_ext(3, args);
}

