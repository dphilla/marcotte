#ifndef _BITS_MMAN_H
#define _BITS_MMAN_H

/*
 * Minimal definitions for Wasm's "memory mapping" environment.
 * Typically, actual calls to mmap/munmap might not be meaningful
 * under Wasm, but we provide these flags and macros so musl-based
 * code compiles without error.
 */

/* Protection bits */
#define PROT_NONE   0x00
#define PROT_READ   0x01
#define PROT_WRITE  0x02
#define PROT_EXEC   0x04

/* Flags for mmap */
#define MAP_SHARED      0x0001
#define MAP_PRIVATE     0x0002
#define MAP_FIXED       0x0010
#define MAP_ANONYMOUS   0x0020
#define MAP_ANON        MAP_ANONYMOUS

/* Additional Linux/musl flags (define as 0 if not used) */
#define MAP_NORESERVE   0x0000
#define MAP_GROWSDOWN   0x0000
#define MAP_DENYWRITE   0x0000
#define MAP_EXECUTABLE  0x0000
#define MAP_LOCKED      0x0000
#define MAP_NONBLOCK    0x0000
#define MAP_STACK       0x0000
#define MAP_HUGETLB     0x0000

/* Return value for mmap failure */
#define MAP_FAILED ((void *)-1)

/* Flags for msync (if implemented) */
#define MS_ASYNC       1
#define MS_INVALIDATE  2
#define MS_SYNC        4

/* Flags for mlock */
#define MCL_CURRENT    1
#define MCL_FUTURE     2
#define MCL_ONFAULT    4 /* optional on some systems */

/* Flags for madvise (if implemented) */
#define MADV_NORMAL          0
#define MADV_RANDOM          1
#define MADV_SEQUENTIAL      2
#define MADV_WILLNEED        3
#define MADV_DONTNEED        4
#define MADV_FREE            8
#define MADV_REMOVE          9
#define MADV_DONTFORK        10
#define MADV_DOFORK          11
#define MADV_HWPOISON        100
#define MADV_SOFT_OFFLINE    101

/*
 * Typical page size in wasm32 is effectively 64 KiB (65536 bytes).
 * We'll define PAGE_SIZE as a stand-in.
 * Some code may reference sysconf(_SC_PAGESIZE) instead.
 */
#define WASM_PAGE_SIZE 65536

#endif /* _BITS_MMAN_H */

