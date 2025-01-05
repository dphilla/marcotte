/**
 * getchar.c
 *
 * Reads the next character from stdin by calling fgetc(stdin).
 */

#include <stdio.h>

int getchar(void)
{
    return fgetc(stdin);
}

