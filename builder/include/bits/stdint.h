#ifndef _BITS_STDINT_H
#define _BITS_STDINT_H

/* These typedefs are typical for a 32-bit environment, but
   you can adjust them as needed for wasm32 if your environment
   differs. */

typedef   signed char       int8_t;
typedef   short             int16_t;
typedef   int               int32_t;
typedef   long long         int64_t;

typedef   unsigned char     uint8_t;
typedef   unsigned short    uint16_t;
typedef   unsigned int      uint32_t;
typedef   unsigned long long uint64_t;

/* “fast” and “least” versions
   In many musl-based arch definitions, you can just define them the same,
   or pick the recommended “fastest” int of at least N bits. */

typedef   int8_t    int_fast8_t;
typedef   int32_t   int_fast16_t;
typedef   int32_t   int_fast32_t;
typedef   int64_t   int_fast64_t;

typedef   uint8_t   uint_fast8_t;
typedef   uint32_t  uint_fast16_t;
typedef   uint32_t  uint_fast32_t;
typedef   uint64_t  uint_fast64_t;

typedef   int8_t    int_least8_t;
typedef   int16_t   int_least16_t;
typedef   int32_t   int_least32_t;
typedef   int64_t   int_least64_t;

typedef   uint8_t   uint_least8_t;
typedef   uint16_t  uint_least16_t;
typedef   uint32_t  uint_least32_t;
typedef   uint64_t  uint_least64_t;

/* pointer-related types */
typedef   long long intptr_t;
typedef   unsigned long long uintptr_t;

/* You can define intmax_t and uintmax_t for 64-bit as well */
typedef long long          intmax_t;
typedef unsigned long long uintmax_t;

#endif /* _BITS_STDINT_H */

