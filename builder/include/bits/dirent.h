#ifndef _BITS_DIRENT_H
#define _BITS_DIRENT_H

/*
 * We assume you have already defined:
 *   ino_t, off_t, etc.
 * in bits/alltypes.h or a similar file. If not, you can define them here:
 *
 *   typedef unsigned long long ino_t;
 *   typedef long long off_t;
 */

/* File type macros for dirent::d_type */
#define DT_UNKNOWN  0
#define DT_FIFO     1
#define DT_CHR      2
#define DT_DIR      4
#define DT_BLK      6
#define DT_REG      8
#define DT_LNK      10
#define DT_SOCK     12
#define DT_WHT      14  /* (optional) whiteout on some filesystems */

/*
 * The dirent structure.
 * - d_ino: inode number
 * - d_off: file offset in the directory stream
 * - d_reclen: the size of this dirent record
 * - d_type: file type (DT_* macros above)
 * - d_name: filename (null-terminated)
 */
struct dirent {
    ino_t  d_ino;
    off_t  d_off;
    unsigned short d_reclen;
    unsigned char  d_type;
    char   d_name[256]; /* or another chosen max length */
};

/*
 * The DIR structure, which is typically opaque.
 * Musl often calls it __dirstream.
 * We'll define it minimally for a Wasm environment.
 * In real usage, you'd store a file descriptor, buffer, etc.
 */
typedef struct __dirstream {
    int fd;
    //DIR base;
    int buf_pos;
    int buf_end;
    unsigned char buffer[4096];
    /* If you need extra fields, add them here. */
} DIR;

#endif /* _BITS_DIRENT_H */

