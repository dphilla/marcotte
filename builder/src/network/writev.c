
/**
 * readv.c
 */
#include <sys/uio.h>
#include <stdint.h>
#include "bits/networking_syscalls.h"
#include "bits/r.h"

ssize_t writev(int fd, const struct iovec *iov, int iovcnt)
{
    ArgDesc args[4];
    int32_t fake_sysno = 999992; // or real readv #, on x86_64: #19 is readv

    args[0].arg_type = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr = &fake_sysno;

    args[1].arg_type = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr = &fd;

    args[2].arg_type = ARGTYPE_PTR_INOUT;
    args[2].size_bytes = iovcnt * sizeof(struct iovec);
    args[2].data_ptr = (void*)iov;

    args[3].arg_type = ARGTYPE_SCALAR;
    args[3].size_bytes = 4;
    args[3].data_ptr = &iovcnt;

    return (ssize_t) create_and_send_buffer_ext(4, args);
}

