#include <stdio.h>
void rewind(FILE *stream)
{
    fseek(stream, 0L, 0 /* SEEK_SET */);
}

