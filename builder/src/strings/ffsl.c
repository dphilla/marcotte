/**
 * ffsl.c
 *
 * Same as ffs, but for a 'long'.
 * Returns the 1-based index of the least significant set bit,
 * or 0 if value is 0.
 */

long ffsl(long x)
{
    if (x == 0) return 0;

    long pos = 1;
    while (!(x & 1)) {
        x >>= 1;
        pos++;
    }
    return pos;
}

