/**
 * getnameinfo.c
 */
#include <netdb.h>
#include <stddef.h>
#include "bits/networking_syscalls.h"
#include "bits/r.h"

int getnameinfo(const struct sockaddr *sa, socklen_t salen,
                char *host, socklen_t hostlen,
                char *serv, socklen_t servlen,
                int flags)
{
  // TODO - test deeply

    // Minimal demonstration: pass everything to host.
    ArgDesc args[7];
    int32_t fake_sysno = 999998; // hypothetical

    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &fake_sysno;

    args[1].arg_type   = ARGTYPE_PTR_IN;
    args[1].size_bytes = salen;
    args[1].data_ptr   = (void*)sa;

    args[2].arg_type   = ARGTYPE_SCALAR;
    args[2].size_bytes = sizeof(socklen_t);
    args[2].data_ptr   = (void*)&salen;

    args[3].arg_type   = ARGTYPE_PTR_OUT;  // fill host buffer
    args[3].size_bytes = hostlen;
    args[3].data_ptr   = host;

    args[4].arg_type   = ARGTYPE_PTR_OUT;  // fill serv buffer
    args[4].size_bytes = servlen;
    args[4].data_ptr   = serv;

    args[5].arg_type   = ARGTYPE_SCALAR;
    args[5].size_bytes = 4;
    args[5].data_ptr   = &flags;

    // We have 6 arguments so far, let's do 6 total
    return create_and_send_buffer_ext(6, args);
}

