  #ifndef _BITS_SOCKET_H
#define _BITS_SOCKET_H

/*
 * Minimal definitions for Wasm’s socket environment.
 * Typically, actual sockets might be stubs or use a custom API.
 * But we provide macros/types so musl-based code compiles.
 *
 * If you haven't defined socklen_t, etc. in <bits/alltypes.h>,
 * do so here. Typically:
 *
 *   typedef unsigned int socklen_t;
 *   typedef unsigned short sa_family_t;
 */

/* Address families (AF_*) */
#define AF_UNSPEC   0
#define AF_UNIX     1
#define AF_INET     2
#define AF_INET6    10
#define AF_MAX      12   /* or some suitable number */

/* Protocol families (PF_*) are usually the same as AF_ macros. */
#define PF_UNSPEC   AF_UNSPEC
#define PF_LOCAL    AF_UNIX
#define PF_INET     AF_INET
#define PF_INET6    AF_INET6

/* Socket types (SOCK_*) */
#define SOCK_STREAM    1
#define SOCK_DGRAM     2
#define SOCK_RAW       3
#define SOCK_RDM       4
#define SOCK_SEQPACKET 5

/* Some flags for send/recv calls (MSG_*) */
#define MSG_OOB        0x0001
#define MSG_PEEK       0x0002
#define MSG_DONTROUTE  0x0004
#define MSG_CTRUNC     0x0008
#define MSG_TRUNC      0x0010
#define MSG_DONTWAIT   0x0020
#define MSG_EOR        0x0040
#define MSG_WAITALL    0x0080
#define MSG_NOSIGNAL   0x4000
#define MSG_MORE       0x8000

/* Level for setsockopt/getsockopt (SOL_SOCKET, etc.) */
#define SOL_SOCKET  1

/* Common sockopt options (SO_*) */
#define SO_DEBUG        1
#define SO_REUSEADDR    2
#define SO_TYPE         3
#define SO_ERROR        4
#define SO_DONTROUTE    5
#define SO_BROADCAST    6
#define SO_SNDBUF       7
#define SO_RCVBUF       8
#define SO_SNDBUFFORCE  32
#define SO_RCVBUFFORCE  33
#define SO_KEEPALIVE    9
#define SO_OOBINLINE    10
#define SO_NO_CHECK     11
#define SO_PRIORITY     12
#define SO_LINGER       13
#define SO_REUSEPORT    15
#define SO_PASSCRED     16
#define SO_PEERCRED     17
#define SO_RCVLOWAT     18
#define SO_SNDLOWAT     19
#define SO_RCVTIMEO     20
#define SO_SNDTIMEO     21
#define SO_ACCEPTCONN   30

/* Shutdown modes */
#define SHUT_RD    0
#define SHUT_WR    1
#define SHUT_RDWR  2

/* Minimal sockaddr, if not defined elsewhere. */
//#ifndef _STRUCT_SOCKADDR
//#define _STRUCT_SOCKADDR
//struct sockaddr {
    //sa_family_t sa_family;
    //char sa_data[14];
//};
//#endif

/*
 * If not defined in <bits/alltypes.h>, define:
 *   typedef unsigned short sa_family_t;
 *   typedef unsigned int   socklen_t;
 *
 * Real code might define them in <bits/alltypes.h>.
 */

/*
 * Additional structures like sockaddr_in, sockaddr_in6, etc.
 * typically live in <netinet/in.h>, not bits/socket.h.
 * We keep this file minimal for the basic socket macros & type.
 */

#endif /* _BITS_SOCKET_H */

