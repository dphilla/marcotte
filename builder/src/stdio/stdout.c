#include <stdio.h>
#include <stdarg.h>   // for variadic
#include <string.h>   // maybe for vsnprintf, etc.

/*
 * We'll define a minimal FILE object for stderr and a global pointer to it.
 * In a real musl, these might be more sophisticated.
 */

/* Just a minimal struct to stand in for a real FILE. */
/*static FILE __stderr_FILE;*/
/*static FILE __stdout_FILE;*/

/*
 * Global pointers:
 *   extern FILE *stderr;
 *   extern FILE *stdout;
 * declared typically in <stdio.h>.
 */
/*FILE *stdout = &__stdout_FILE;*/

