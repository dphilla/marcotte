/**
 * inet_pton.c
 */
#include <arpa/inet.h>
#include <string.h>
#include "bits/networking_syscalls.h"
#include "bits/r.h"

int inet_pton(int af, const char *src, void *dst)
{
    // your ArgDesc approach
    // for demonstration:
    ArgDesc args[4];
    int32_t fake_sysno = 999; // or real if you have a custom

    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &fake_sysno;

    args[1].arg_type   = ARGTYPE_SCALAR;
    args[1].size_bytes = 4;
    args[1].data_ptr   = &af;

    size_t len = src ? (strlen(src) + 1) : 0;
    args[2].arg_type   = ARGTYPE_PTR_IN;
    args[2].size_bytes = len;
    args[2].data_ptr   = (void*)src;

    // dst is a pointer out
    // If AF_INET => 4 bytes, AF_INET6 => 16 bytes, etc.
    // You can guess from `af` or pass a max like 16
    args[3].arg_type   = ARGTYPE_PTR_OUT;
    args[3].size_bytes = (af == AF_INET6) ? 16 : 4;
    args[3].data_ptr   = dst;

    int ret = create_and_send_buffer_ext(4, args);
    return ret;
}

