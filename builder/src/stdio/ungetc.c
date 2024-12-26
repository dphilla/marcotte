#include <stdio.h>

int ungetc(int c, FILE *stream)
{
    /* Real ungetc needs a pushback buffer. For simplicity, we just fail. */
    // TODO - imple later, much later
    (void)c; (void)stream;
    return EOF;
}

