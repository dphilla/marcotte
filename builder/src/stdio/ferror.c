#include <stdio.h>
int ferror(FILE *stream)
{
    return (stream && stream->error) ? 1 : 0;
}

