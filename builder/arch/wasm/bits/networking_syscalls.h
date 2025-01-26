#ifndef NETWORKING_SYSCALLS_H
#define NETWORKING_SYSCALLS_H

//x86_64 support only for now
// Socket Management
#define SYS_socket       41
#define SYS_bind         49
#define SYS_listen       50
#define SYS_accept       43
#define SYS_accept4      288
#define SYS_connect      42
#define SYS_socketpair   53
#define SYS_shutdown     48
#define SYS_getsockname  51
#define SYS_getpeername  52

// Data Transfer
#define SYS_sendto       44
#define SYS_recvfrom     45
#define SYS_sendmsg      46
#define SYS_recvmsg      47
#define SYS_sendfile     40
#define SYS_sendmmsg     307
#define SYS_recvmmsg     299

// Socket Options
#define SYS_setsockopt   54
#define SYS_getsockopt   55

// Polling/Multiplexing
#define SYS_poll         7
#define SYS_select       23
#define SYS_epoll_create 213
#define SYS_epoll_create1 291
#define SYS_epoll_ctl    233
#define SYS_epoll_wait   232
#define SYS_epoll_pwait  281

// Event Notification
#define SYS_signalfd     282
#define SYS_signalfd4    289
#define SYS_eventfd      284
#define SYS_eventfd2     290

#endif // NETWORKING_SYSCALLS_H

