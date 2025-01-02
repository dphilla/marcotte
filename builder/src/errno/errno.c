// builder/src/errno/errno.c
#include <errno.h>

// We define a static variable to hold "errno" globally.
// In real musl, it's often thread-local. For a simple stub, we do this:
static int s_my_errno;

int *__errno_location(void)
{
    return &s_my_errno;
}

