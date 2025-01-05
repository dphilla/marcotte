/**
 * getaddrinfo.c
 *   Typically a library call, but we can treat it as a "virtual" syscall #?
 */
#include <netdb.h>
#include <string.h>
#include "bits/networking_syscalls.h"
#include "bits/r.h"

int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res)
{
  //TODO
    // This is complex in reality. We'll do a simple approach:
    // We'll pass node/service/hints, the host does real getaddrinfo,
    // returns a single or multiple results. We store them in a single blob
    // or patch multiple times. Real code needs more advanced patching or custom protocol.
    // For now, we do a placeholder:

    ArgDesc args[4];

    int32_t fake_sysno = 999999; // Not a real Linux syscall, but for demonstration
    args[0].arg_type   = ARGTYPE_SCALAR;
    args[0].size_bytes = 4;
    args[0].data_ptr   = &fake_sysno;

    // node pointer
    size_t node_len = node ? strlen(node)+1 : 0;
    args[1].arg_type   = ARGTYPE_PTR_IN;
    args[1].size_bytes = node_len;
    args[1].data_ptr   = (void*)node;

    // service pointer
    size_t svc_len = service ? strlen(service)+1 : 0;
    args[2].arg_type   = ARGTYPE_PTR_IN;
    args[2].size_bytes = svc_len;
    args[2].data_ptr   = (void*)service;

    // hints pointer
    // ignoring size beyond basic struct
    args[3].arg_type   = ARGTYPE_PTR_IN;
    args[3].size_bytes = hints ? sizeof(struct addrinfo) : 0;
    args[3].data_ptr   = (void*)hints;

    int ret = create_and_send_buffer_ext(4, args);
    if (ret == 0) {
        // The server might patch a suitable addrinfo back.
        // We do not show that patch logic here.
        // You’d store it in *res. So *res must be allocated or pointed.
        // Real code is more elaborate. This is just a minimal demonstration.
        *res = NULL;
    }
    return ret;
}
