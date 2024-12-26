#include <stdio.h>
#include <string.h>

char *mktemp(char *template)
{
    /* Insecure function, but we do a naive approach: replace 'XXXXXX' with random digits. */
    if (!template) return NULL;
    char *p = strstr(template, "XXXXXX");
    if (!p) return template;
    /* Replace with a naive "123456" for demo. In real code, random. */
    p[0] = '1'; p[1] = '2'; p[2] = '3'; p[3] = '4'; p[4] = '5'; p[5] = '6';
    return template;
}

