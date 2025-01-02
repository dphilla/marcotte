#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
    if (!str || size == 0) return 0;
    // For a real implementation, you'd parse 'format' properly.
    // Let's do a naive approach that only handles %s, %d, %c, and inserts no expansions otherwise.

    // We'll build up a buffer manually:
    size_t pos = 0;
    const char *p = format;
    while (*p && pos < (size - 1)) {
        if (*p == '%') {
            p++;
            if (*p == 's') {
                const char *arg_s = va_arg(ap, const char *);
                if (!arg_s) arg_s = "(null)";
                while (*arg_s && pos < (size - 1)) {
                    str[pos++] = *arg_s++;
                }
                p++;
            } else if (*p == 'd') {
                int arg_d = va_arg(ap, int);
                // Convert to string:
                char temp[32];
                snprintf(temp, sizeof(temp), "%d", arg_d);
                const char *tmp = temp;
                while (*tmp && pos < (size - 1)) {
                    str[pos++] = *tmp++;
                }
                p++;
            } else if (*p == 'c') {
                int arg_c = va_arg(ap, int);
                if (pos < (size - 1)) {
                    str[pos++] = (char)arg_c;
                }
                p++;
            } else {
                // unrecognized format specifier, just copy it literally?
                if (pos < (size - 1)) {
                    str[pos++] = '%';
                }
                continue;
            }
        } else {
            str[pos++] = *p++;
        }
    }
    str[pos] = '\0';
    // We return the would-be length if fully expanded, ignoring truncation issues for simplicity:
    // A real vsnprintf returns the total length. We'll just do pos:
    return (int)pos;
}

