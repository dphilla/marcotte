/**
 * remove.c
 */
#include <unistd.h>

int remove(const char *pathname)
{
  unlink(pathname);
}
