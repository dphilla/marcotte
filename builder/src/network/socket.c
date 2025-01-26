/**
 * socket.c
 *
 * This is the Marcotte-proxied implementation of socket().
 * It sends [SYS_socket, domain, type, protocol] to the host,
 * waits for the real socket() result, and returns it.
 */

#include <sys/socket.h>
#include <stdint.h>
#include "bits/r.h"   // for ArgDesc, ARGTYPE_SCALAR, create_and_send_buffer_ext

int socket(int domain, int type, int protocol)
{
    // We'll have 4 total arguments in our ArgDesc array:
    //   1) The syscall number (SYS_socket = 41)
    //   2) domain
    //   3) type
    //   4) protocol
    ArgDesc args[4];

    // Arg #0: SCALAR => syscall number
    int32_t sysno = 41;
    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = sizeof(int32_t);
    args[0].data_ptr   = &sysno;

    // Arg #1: domain as SCALAR
    args[1].arg_type   = ARGTYPE_SCALAR;
    args[1].size_bytes = sizeof(int32_t);
    args[1].data_ptr   = &domain;

    // Arg #2: type as SCALAR
    args[2].arg_type   = ARGTYPE_SCALAR;
    args[2].size_bytes = sizeof(int32_t);
    args[2].data_ptr   = &type;

    // Arg #3: protocol as SCALAR
    args[3].arg_type   = ARGTYPE_SCALAR;
    args[3].size_bytes = sizeof(int32_t);
    args[3].data_ptr   = &protocol;

    // Call our helper to proxy the syscall and return the result
    int fd = create_and_send_buffer_ext(4, args);
    return fd;
}

