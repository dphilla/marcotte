#ifndef _BITS_STAT_H
#define _BITS_STAT_H

/*
 * For a typical Musl-like environment, we assume you have:
 *   - dev_t
 *   - ino_t
 *   - mode_t
 *   - nlink_t
 *   - uid_t
 *   - gid_t
 *   - off_t
 *   - blksize_t
 *   - blkcnt_t
 *   - time_t
 * defined in <bits/alltypes.h> or a similar header.
 * We also assume you have struct timespec with time_t tv_sec; long tv_nsec;
 * somewhere (e.g., <bits/alltypes.h> or <bits/time.h>).
 */

   //typedef unsigned long dev_t;
   //typedef unsigned long ino_t;
   //typedef unsigned int  mode_t;
   //typedef unsigned int  nlink_t;
   //typedef unsigned int  uid_t;
   //typedef unsigned int  gid_t;
   //typedef long long     off_t;
   //typedef long long     blkcnt_t;
   //typedef long          blksize_t;
   //typedef long long     time_t;
   struct timespec { time_t tv_sec; long tv_nsec; };


/* Standard file type and mode macros (from POSIX / typical musl bits). */
#define S_IFMT   0170000  /* type of file */
#define S_IFSOCK 0140000  /* socket */
#define S_IFLNK  0120000  /* symbolic link */
#define S_IFREG  0100000  /* regular */
#define S_IFBLK  0060000  /* block device */
#define S_IFDIR  0040000  /* directory */
#define S_IFCHR  0020000  /* character device */
#define S_IFIFO  0010000  /* FIFO */
#define S_ISUID  04000    /* set user id on execution */
#define S_ISGID  02000    /* set group id on execution */
#define S_ISVTX  01000    /* sticky bit */
#define S_IRWXU  00700
#define S_IRUSR  00400
#define S_IWUSR  00200
#define S_IXUSR  00100
#define S_IRWXG  00070
#define S_IRGRP  00040
#define S_IWGRP  00020
#define S_IXGRP  00010
#define S_IRWXO  00007
#define S_IROTH  00004
#define S_IWOTH  00002
#define S_IXOTH  00001

/* Check macros */
#define S_ISREG(m)  (((m) & S_IFMT) == S_IFREG)
#define S_ISDIR(m)  (((m) & S_IFMT) == S_IFDIR)
#define S_ISCHR(m)  (((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m)  (((m) & S_IFMT) == S_IFBLK)
#define S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)
#define S_ISLNK(m)  (((m) & S_IFMT) == S_IFLNK)
#define S_ISSOCK(m) (((m) & S_IFMT) == S_IFSOCK)

/*
 * The main stat structure for WASM (64-bit offsets, 64-bit times, etc.).
 * This is based on a typical musl approach for 32-bit or 64-bit arches.
 */
struct stat {
    dev_t          st_dev;
    ino_t          st_ino;
    mode_t         st_mode;
    nlink_t        st_nlink;
    uid_t          st_uid;
    gid_t          st_gid;
    dev_t          st_rdev;
    off_t          st_size;
    blksize_t      st_blksize;
    blkcnt_t       st_blocks;

    /* Timestamps as 'struct timespec':
     *   st_atim, st_mtim, st_ctim
     * For backward compatibility, you can also define st_atime, st_mtime, st_ctime macros.
     */
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;

    /* In many musl arch ports, a few unused fields:
     *   For alignment or future expansion.
     */
    long __unused[3];
};

/* Traditional macros to access just the seconds of the time fields. */
#define st_atime st_atim.tv_sec
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec

#endif /* _BITS_STAT_H */

