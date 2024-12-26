#include <stdio.h>

void clearerr(FILE *stream)
{
    if (stream) {
        stream->error = 0;
        stream->eof   = 0;
    }
}

