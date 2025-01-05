/**
 * inet_ntoa.c
 */
#include <arpa/inet.h>   // for struct in_addr
#include "bits/r.h"      // ArgDesc, etc.

// The musl declaration is `char *inet_ntoa(struct in_addr in);`
char *inet_ntoa(struct in_addr in)
{
    // Typically returns a pointer to a static buffer or so.
    // For your Marcotte approach, you'd do a "fake" system call or local logic:
    static char buffer[16]; // e.g. "255.255.255.255\0"

    // For example, do an ArgDesc call with the 32-bit address:
    // but let's just do a minimal placeholder:
    // ...
    // Then fill `buffer` with the dotted-decimal form.

    // For demonstration, let's pretend:
    unsigned long addr = in.s_addr;
    // do real numeric -> dotted logic or call your proxy.

    // PSE:
    // ArgDesc args[2], call, server returns string, copy to buffer, etc.

    // Return pointer to static.
    return buffer;
}

