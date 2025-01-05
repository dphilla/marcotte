/**
 * putchar.c
 *
 * Writes a character to stdout by calling fputc(stdout).
 */

#include <stdio.h>

int putchar(int c)
{
    return fputc(c, stdout);
}

