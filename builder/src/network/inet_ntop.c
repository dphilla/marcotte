// These are typically library calls that do textual conversions, not real syscalls
/**
 * inet_pron.c
 */
#include <arpa/inet.h>
#include <string.h>
#include "bits/networking_syscalls.h"
#include "bits/r.h"

int ntop(const char *cp, struct in_addr *inp)
{
    // A library function that converts text to an in_addr.
    // We'll do a 'fake' syscall approach:
    ArgDesc args[3];
    int32_t fake_sysno = 999997;

    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &fake_sysno;

    size_t cplen = cp ? (strlen(cp)+1) : 0;
    args[1].arg_type   = ARGTYPE_PTR_IN;
    args[1].size_bytes = cplen;
    args[1].data_ptr   = (void*)cp;

    args[2].arg_type   = ARGTYPE_PTR_OUT;
    args[2].size_bytes = sizeof(struct in_addr);
    args[2].data_ptr   = inp;

    int ret = create_and_send_buffer_ext(3, args);
    return (ret == 1) ? 1 : 0; // typically returns 1 on success, 0 on failure
}


