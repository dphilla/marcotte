#define _REDIR_TIME64 1
#define _Addr int32_t      // Wasm uses 32-bit addressing
#define _Int64 int64_t     // WebAssembly has support for 64-bit integers
#define _Reg int32_t       // Registers are 32-bit by default in WebAssembly

// WebAssembly is little-endian, so set __BYTE_ORDER accordingly
#define __BYTE_ORDER 1234

// WebAssembly typically has a 32-bit `long`, so we set __LONG_MAX to the 32-bit max
#define __LONG_MAX 0x7fffffffL

#ifndef __cplusplus
typedef unsigned i32;  // Define wchar_t as an unsigned 32-bit integer
#endif

typedef float f32;          // Use native `float` for float_t in Wasm
typedef double f64;        // Use native `double` for double_t in Wasm

// Ensure max_align_t accounts for the strictest alignment on Wasm, which is 64-bit for `long long`
typedef struct {
    int64_t __ll;              // Use 64-bit integer
    long double __ld;          // Long double alignment for precision calculations
} max_align_t;

//// Define basic types commonly used in musl for WebAssembly

// socklen_t is used for sizes of socket-related values, typically an unsigned 32-bit integer
typedef unsigned int socklen_t;

// sa_family_t is an address family type, typically an unsigned 16-bit integer
typedef unsigned short sa_family_t;

// size_t is used for sizes of objects in memory, and on WebAssembly, it is 32-bit
typedef unsigned int size_t;

// ssize_t is the signed counterpart of size_t, used for functions that return either sizes or -1 on error
typedef int ssize_t;

// uid_t represents user IDs, typically a 32-bit unsigned integer
typedef unsigned int uid_t;

// pid_t represents process IDs, typically a 32-bit signed integer
typedef int pid_t;

// gid_t represents group IDs, typically a 32-bit unsigned integer
typedef unsigned int gid_t;

// struct iovec is used for scatter-gather I/O, typically defined as follows:
struct iovec {
    void *iov_base;   // Pointer to data
    size_t iov_len;   // Length of data
};

// time_t is typically a 64-bit signed integer to handle large time values, compatible with WASI's 64-bit timestamps
typedef long long time_t;

// off_t is used for file sizes and offsets, typically a 64-bit signed integer for larger files
typedef long long off_t;

