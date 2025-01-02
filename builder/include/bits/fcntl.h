#ifndef _BITS_FCNTL_H
#define _BITS_FCNTL_H

/* File access modes */
#define O_RDONLY    0
#define O_WRONLY    1
#define O_RDWR      2

/* File creation flags */
#define O_CREAT     0100
#define O_EXCL      0200
#define O_NOCTTY    0400
#define O_TRUNC     01000

/* File status flags (used with open/fcntl) */
#define O_APPEND    02000
#define O_NONBLOCK  04000
#define O_DSYNC     010000
#define FASYNC      020000
#define O_DIRECT    040000
#define O_LARGEFILE 0100000
#define O_DIRECTORY 0200000
#define O_NOFOLLOW  0400000
#define O_NOATIME   01000000
#define O_CLOEXEC   02000000

/* For posix_fadvise */
#define POSIX_FADV_NORMAL       0
#define POSIX_FADV_RANDOM       1
#define POSIX_FADV_SEQUENTIAL   2
#define POSIX_FADV_WILLNEED     3
#define POSIX_FADV_DONTNEED     4
#define POSIX_FADV_NOREUSE      5

/* For fcntl */
#define F_DUPFD         0
#define F_GETFD         1
#define F_SETFD         2
#define F_GETFL         3
#define F_SETFL         4
#define F_GETLK         5
#define F_SETLK         6
#define F_SETLKW        7
#define F_GETOWN        9
#define F_SETOWN        8
#define F_GETSIG        11
#define F_SETSIG        10
#define F_SETOWN_EX     15
#define F_GETOWN_EX     16
#define F_GETLK64       12
#define F_SETLK64       13
#define F_SETLKW64      14

/* For lock operations */
#define F_RDLCK         0
#define F_WRLCK         1
#define F_UNLCK         2

/* FD flags (for F_GETFD / F_SETFD) */
#define FD_CLOEXEC      1

/* At this time, you might not implement everything on wasm,
   but let's keep these macros so code compiles. */


#endif /* _BITS_FCNTL_H */

