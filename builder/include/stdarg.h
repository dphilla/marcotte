#ifndef _STDARG_H
#define _STDARG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bits/alltypes.h>

/*
 * Now define the standard macros that call the Clang intrinsics:
 * For example:
 */
#define va_start(ap, last)  __builtin_va_start(ap, last)
#define va_end(ap)          __builtin_va_end(ap)
#define va_arg(ap, type)    __builtin_va_arg(ap, type)
#define va_copy(d, s)       __builtin_va_copy(d, s)

#ifdef __cplusplus
}
#endif

#endif /* _STDARG_H */

