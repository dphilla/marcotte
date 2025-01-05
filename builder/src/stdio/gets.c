/**
 * gets.c
 *
 * Highly unsafe function, removed from C11.
 * We'll do a minimal stub that calls fgets() but strips the newline.
 */

#include <stdio.h>
#include <string.h>

char *gets(char *s)
{
    // A very simplistic approach:
    //  - calls fgets(s, some_big_size, stdin)
    //  - strips newline if present
    //  - returns NULL on EOF or error

    // TODO -
    // If you have no safe way to guess the buffer size, there's no real fix.
    // For demonstration, let's pick a large arbitrary size:
    char *res = fgets(s, 65536, stdin);
    if (!res) return NULL;

    // Strip trailing newline
    size_t len = 0;
    while (s[len] && s[len] != '\n') len++;
    if (s[len] == '\n') s[len] = '\0';

    return s;
}

