//In musl: this would normally be generated on the arch from the alltypes.h.in files
//and stitched together, but since this is just for Wasm, we have those all copied
//and available here without needing it in the build step.
//
#ifdef SOME_CUSTOM_ATTRIBUTE
#  define TYPEDEF __attribute__((whatever)) typedef
#else
#  define TYPEDEF typedef
#endif

//#define __LITTLE_ENDIAN 1234
//#define __BIG_ENDIAN 4321
//#define __USE_TIME_BITS64 1

//TYPEDEF unsigned _Addr size_t;
//TYPEDEF unsigned _Addr uintptr_t;
//TYPEDEF _Addr ptrdiff_t;
//TYPEDEF _Addr ssize_t;
//TYPEDEF _Addr intptr_t;
//TYPEDEF _Addr regoff_t;
//TYPEDEF _Reg register_t;
//TYPEDEF _Int64 time_t;
//TYPEDEF _Int64 suseconds_t;

//TYPEDEF signed char     int8_t;
//TYPEDEF signed short    int16_t;
//TYPEDEF signed int      int32_t;
//TYPEDEF signed _Int64   int64_t;
//TYPEDEF signed _Int64   intmax_t;
//TYPEDEF unsigned char   uint8_t;
//TYPEDEF unsigned short  uint16_t;
//TYPEDEF unsigned int    uint32_t;
//TYPEDEF unsigned _Int64 uint64_t;
//TYPEDEF unsigned _Int64 u_int64_t;
//TYPEDEF unsigned _Int64 uintmax_t;

//TYPEDEF unsigned mode_t;
//TYPEDEF unsigned _Reg nlink_t;
//TYPEDEF _Int64 off_t;
//TYPEDEF unsigned _Int64 ino_t;
//TYPEDEF unsigned _Int64 dev_t;
//TYPEDEF long blksize_t;
//TYPEDEF _Int64 blkcnt_t;
//TYPEDEF unsigned _Int64 fsblkcnt_t;
//TYPEDEF unsigned _Int64 fsfilcnt_t;

//TYPEDEF unsigned wint_t;
//TYPEDEF unsigned long wctype_t;

//TYPEDEF void * timer_t;
//TYPEDEF int clockid_t;
//TYPEDEF long clock_t;
//STRUCT timeval { time_t tv_sec; suseconds_t tv_usec; };
//STRUCT timespec { time_t tv_sec; int :8*(sizeof(time_t)-sizeof(long))*(__BYTE_ORDER==4321); long tv_nsec; int :8*(sizeof(time_t)-sizeof(long))*(__BYTE_ORDER!=4321); };

//TYPEDEF int pid_t;
//TYPEDEF unsigned id_t;
//TYPEDEF unsigned uid_t;
//TYPEDEF unsigned gid_t;
//TYPEDEF int key_t;
//TYPEDEF unsigned useconds_t;

//#ifdef __cplusplus
//TYPEDEF unsigned long pthread_t;
//#else
//TYPEDEF struct __pthread * pthread_t;
//#endif
//TYPEDEF int pthread_once_t;
//TYPEDEF unsigned pthread_key_t;
//TYPEDEF int pthread_spinlock_t;
//TYPEDEF struct { unsigned __attr; } pthread_mutexattr_t;
//TYPEDEF struct { unsigned __attr; } pthread_condattr_t;
//TYPEDEF struct { unsigned __attr; } pthread_barrierattr_t;
//TYPEDEF struct { unsigned __attr[2]; } pthread_rwlockattr_t;

//STRUCT _IO_FILE { char __x; };
//TYPEDEF struct _IO_FILE FILE;

//TYPEDEF __builtin_va_list va_list;
//TYPEDEF __builtin_va_list __isoc_va_list;

//TYPEDEF struct __mbstate_t { unsigned __opaque1, __opaque2; } mbstate_t;

//TYPEDEF struct __locale_struct * locale_t;

//TYPEDEF struct __sigset_t { unsigned long __bits[128/sizeof(long)]; } sigset_t;

//STRUCT iovec { void *iov_base; size_t iov_len; };

//STRUCT winsize { unsigned short ws_row, ws_col, ws_xpixel, ws_ypixel; };

//TYPEDEF unsigned socklen_t;
//TYPEDEF unsigned short sa_family_t;

//TYPEDEF struct { union { int __i[sizeof(long)==8?14:9]; volatile int __vi[sizeof(long)==8?14:9]; unsigned long __s[sizeof(long)==8?7:9]; } __u; } pthread_attr_t;
//TYPEDEF struct { union { int __i[sizeof(long)==8?10:6]; volatile int __vi[sizeof(long)==8?10:6]; volatile void *volatile __p[sizeof(long)==8?5:6]; } __u; } pthread_mutex_t;
//TYPEDEF struct { union { int __i[sizeof(long)==8?10:6]; volatile int __vi[sizeof(long)==8?10:6]; volatile void *volatile __p[sizeof(long)==8?5:6]; } __u; } mtx_t;
//TYPEDEF struct { union { int __i[12]; volatile int __vi[12]; void *__p[12*sizeof(int)/sizeof(void*)]; } __u; } pthread_cond_t;
//TYPEDEF struct { union { int __i[12]; volatile int __vi[12]; void *__p[12*sizeof(int)/sizeof(void*)]; } __u; } cnd_t;
//TYPEDEF struct { union { int __i[sizeof(long)==8?14:8]; volatile int __vi[sizeof(long)==8?14:8]; void *__p[sizeof(long)==8?7:8]; } __u; } pthread_rwlock_t;
//TYPEDEF struct { union { int __i[sizeof(long)==8?8:5]; volatile int __vi[sizeof(long)==8?8:5]; void *__p[sizeof(long)==8?4:5]; } __u; } pthread_barrier_t;

#undef _Addr
#undef _Int64
#undef _Reg

//Wasm-specific to end of file
#ifndef _ALLTYPES_H
#define _ALLTYPES_H

/*
 * Indicate we are using 64-bit time syscalls internally (e.g., time64).
 * In musl, _REDIR_TIME64 is used to redirect older 32-bit time calls
 * to 64-bit versions. We mimic that here for future-proofness.
 */
#define _REDIR_TIME64 1

/*
 * Basic pointer/address definitions for wasm32:
 *  - _Addr: pointer register size (32 bits).
 *  - _Reg:  general-purpose register (32 bits).
 *  - _Int64: 64-bit integer type.
 */
#define _Addr   int32_t
#define _Reg    int32_t
#define _Int64  int64_t

/*
 * WebAssembly is little-endian:
 *  - Typically, __BYTE_ORDER = 1234 for little endian,
 *    4321 for big endian. We set 1234.
 */
#define __BYTE_ORDER 1234

/*
 * Because wasm32 typically treats 'long' as 32 bits,
 * we set __LONG_MAX to the 32-bit max.
 */
#define __LONG_MAX 0x7fffffffL

/*
 * For C++, 'wchar_t' is a built-in type. In plain C, we define
 * 'wchar_t' as a 32-bit unsigned integer (common in musl).
 */
#ifndef __cplusplus
typedef unsigned int wchar_t;
#endif

/*
 * For 'float_t' and 'double_t' (used in <math.h>),
 * we use the standard built-in float/double on wasm32.
 */
typedef float  float_t;
typedef double double_t;

/*
 * max_align_t must represent the type with the strictest alignment
 * requirement. On wasm32, 8-byte alignment is typically enough to
 * cover 64-bit data. If you emulate 128-bit long double, adjust as needed.
 */
typedef struct {
    long long   __ll;  /* force 8-byte alignment */
    long double __ld;  /* handle alignment for 'long double' if larger */
} max_align_t;

/*
 * Common types typically defined in musl or POSIX headers, adapted for wasm32:
 */

/* socklen_t: size of socket-related values, 32-bit */
typedef unsigned int socklen_t;

/* sa_family_t: address family type, usually 16-bit */
typedef unsigned short sa_family_t;

/* size_t: for object sizes, 32-bit on wasm32 */
typedef unsigned int size_t;

/* ssize_t: signed version of size_t, 32-bit on wasm32 */
typedef int ssize_t;

/* uid_t: user ID (32-bit) */
typedef unsigned int uid_t;

/* gid_t: group ID (32-bit) */
typedef unsigned int gid_t;

/* pid_t: process ID (32-bit) */
typedef int pid_t;

/*
 * Scatter-gather I/O structure
 */
struct iovec {
    void  *iov_base;  /* Base address of a memory region */
    size_t iov_len;   /* The size of the memory region */
};

/*
 * time_t:
 *  - 64-bit to avoid Y2038 issues (common approach in modern libc).
 */
typedef long long time_t;

/*
 * off_t:
 *  - file offsets and sizes, use 64-bit for large file support.
 */
typedef long long off_t;

/*
 * Additional file-system types:
 *
 * dev_t: device number, often 64-bit (to hold major/minor device info).
 * ino_t: inode number, also commonly 64-bit for large filesystems.
 * mode_t: file mode bits (permissions + type), typically 32-bit.
 * nlink_t: link count for files, typically 32-bit.
 * blksize_t: block size used in stat, typically 64-bit if large sizes are possible.
 * blkcnt_t: block count for file usage, also 64-bit.
 */
typedef unsigned long long dev_t;
typedef unsigned long long ino_t;
typedef unsigned int       mode_t;
typedef unsigned int       nlink_t;
typedef long long          blksize_t;
typedef long long          blkcnt_t;

/*
 * clock_t: used for clock ticks (e.g., times(), clock()).
 * In many 32-bit ABIs, it's a 32-bit signed "long".
 * We'll match that here.
 */
typedef int clock_t;

/*
 * suseconds_t: microsecond count in some syscalls (e.g., struct timeval).
 * Typically a signed 32-bit integer in musl on 32-bit arch.
 */
typedef int suseconds_t;

/*
 * useconds_t: microsecond count for usleep, etc.
 * Typically an unsigned 32-bit integer.
 */
typedef unsigned int useconds_t;

/*
 * sigset_t: signal set representation. In musl on 32-bit arch,
 * it's usually a struct with an array of longs. We'll store 64 signals
 * in 2 x 32-bit bitmasks for simplicity.
 *
 * If you want to handle more signals, expand the array.
 */
typedef struct {
    unsigned int __bits[2]; /* 64 possible signals */
} sigset_t;

#include <stdint.h>

//typedef struct {
    //uint32_t arg_start;
    //uint32_t arg_current;
    //uint32_t arg_end;
//} __isoc_va_list;

typedef __builtin_va_list va_list;
typedef __builtin_va_list __isoc_va_list;

typedef __isoc_va_list va_list;
//typedef __builtin_va_list va_list;
//typedef __builtin_va_list __isoc_va_list;

#define va_start(ap, last) \
    do { \
        (ap).arg_start = (uint32_t)&(last) + sizeof(last); \
        (ap).arg_current = (ap).arg_start; \
    } while (0)

#define va_arg(ap, type) \
    ({ \
        type *arg_ptr = (type *)(ap.arg_current); \
        (ap).arg_current += sizeof(type); \
        *arg_ptr; \
    })

#define va_end(ap) \
    do { \
        (ap).arg_start = (ap).arg_current = 0; \
    } while (0)

//__builtin_va_list
//

typedef struct {
    const char *ctype;
    const char *numeric;
    const char *time;
    const char *collate;
    const char *monetary;
    const char *messages;
} locale_t;


/* 2) The standard fixed-width types are typically in bits/stdint.h,
 *    but we can also define them here if needed:
 *
 * e.g.
 * typedef   signed char      int8_t;
 * typedef   short            int16_t;
 * typedef   int              int32_t;
 * typedef   long long        int64_t;
 * ...
 * etc.
 * (You may rely on bits/stdint.h instead.)
 */

/* 3) Misc system types. */
typedef long long          fsblkcnt_t;
typedef long long          fsfilcnt_t;

/*
 * fpos_t often is a struct or an integer type
 * In many musl ports, it might be 'typedef long long fpos_t;'
 * or a struct containing an off_t plus some state.
 * If your code does (long)*pos, using an integer is simplest:
 */
//typedef long long          fpos_t;

/*
 * You can also define a 32-bit version if you prefer:
 *   typedef long fpos_t;
 * But watch out for code that expects 64-bit.
 */

/* 5) struct stat, struct timespec, etc., might be declared in other bits headers.
 *   We'll omit them for brevity.
 */

/* 6) Macros for pointer-sized limits, if needed. */
/* e.g., #define SIZE_MAX  0xffffffffu on a 32-bit */


// If your environment doesn't define 'suseconds_t', define it here.
// Typically it's a signed integer type for microseconds.
// In musl it is often a typedef in bits/alltypes.h.
// We'll guess a 64-bit for simplicity:
//typedef long suseconds_t;

// Provide the real definition of struct timeval
#ifndef __DEFINED_struct_timeval
#define __DEFINED_struct_timeval
struct timeval {
    time_t tv_sec;        // seconds
    suseconds_t tv_usec;  // microseconds
};
#endif

// If sys/time.h references struct itimerval, define it:
//#ifndef __DEFINED_struct_itimerval
//#define __DEFINED_struct_itimerval
//struct itimerval {
    //struct timeval it_interval;
    //struct timeval it_value;
//};
//#endif

#endif /* _ALLTYPES_H */
