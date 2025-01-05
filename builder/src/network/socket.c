#include <sys/socket.h>
#include <stdarg.h>

// defined in r.c
static int32_t create_and_send_buffer(int num_args, ...);

int socket(int domain, int type, int protocol)
{
    int32_t result = create_and_send_buffer(SYS_socket, domain, type, protocol);

    return result;
}

