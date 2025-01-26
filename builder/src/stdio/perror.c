#include <stdio.h>
#include <errno.h>
#include "string.h"

void perror(const char *s)
{
  //TODO - when Proc is extracted, pkc, etc.
    /* might not have a global 'errno' in your environment, but let's pretend. */

    /*extern int errno;*/
    /* Just print a minimal message. */
    /*if (s && s[0]) {*/
        /*fprintf(stderr, "%s: error %d\n", s, errno);*/
    /*} else {*/
        /*fprintf(stderr, "error %d\n", errno);*/
    /*}*/
}

