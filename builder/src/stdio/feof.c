#include <stdio.h>
int feof(FILE *stream)
{
    return (stream && stream->eof) ? 1 : 0;
}

