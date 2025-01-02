#ifndef _BITS_IOCTL_H
#define _BITS_IOCTL_H

/*
 * Minimal definitions for WASM.
 * If your environment doesn't actually implement these ioctls,
 * you can still define them so references won't break the build.
 */

/*
 * Base macros for building request codes:
 *  _IOC(dir,type,nr,size)
 *  _IO(type,nr)
 *  _IOR(type,nr,size)
 *  _IOW(type,nr,size)
 *  _IOWR(type,nr,size)
 */

/* The "direction" bits: read=2, write=1, none=0 in Linux-like systems */
#define _IOC_NRBITS   8
#define _IOC_TYPEBITS 8
#define _IOC_SIZEBITS 14
#define _IOC_DIRBITS  2

#define _IOC_NRSHIFT    0
#define _IOC_TYPESHIFT  (_IOC_NRSHIFT + _IOC_NRBITS)
#define _IOC_SIZESHIFT  (_IOC_TYPESHIFT + _IOC_TYPEBITS)
#define _IOC_DIRSHIFT   (_IOC_SIZESHIFT + _IOC_SIZEBITS)

/* Direction bits */
#define _IOC_NONE  0U
#define _IOC_WRITE 1U
#define _IOC_READ  2U

/* Construct an ioctl request code. */
#define _IOC(dir,type,nr,size) \
  ( ((dir)  << _IOC_DIRSHIFT)  | \
    ((type) << _IOC_TYPESHIFT) | \
    ((nr)   << _IOC_NRSHIFT)   | \
    ((size) << _IOC_SIZESHIFT) )

/* For macros that have no size argument or it’s an integer. */
#define _IO(type,nr)           _IOC(_IOC_NONE,(type),(nr),0)
#define _IOR(type,nr,size)     _IOC(_IOC_READ,(type),(nr),sizeof(size))
#define _IOW(type,nr,size)     _IOC(_IOC_WRITE,(type),(nr),sizeof(size))
#define _IOWR(type,nr,size)    _IOC(_IOC_READ|_IOC_WRITE,(type),(nr),sizeof(size))

/*
 * Example: Terminal ioctls (as placeholders).
 * Typically defined in <asm-generic/termbits.h> or <asm/ioctls.h>.
 * We'll just define a couple so references to TIOCGWINSZ / TIOCSWINSZ won't break.
 */
#define TIOCGWINSZ  _IOR('t', 104, struct winsize)
#define TIOCSWINSZ  _IOW('t', 103, struct winsize)

/* If your code uses a struct winsize, you can define a minimal version here: */
struct winsize {
    unsigned short ws_row;
    unsigned short ws_col;
    unsigned short ws_xpixel;
    unsigned short ws_ypixel;
};

/*
 * Add any other ioctls your musl code references.
 * If your environment doesn't implement them, define them as stubs.
 */

#endif /* _BITS_IOCTL_H */

