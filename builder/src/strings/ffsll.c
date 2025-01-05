/**
 * ffsll.c
 *
 * Same as ffs, but for a 'long long'.
 * Returns 1-based index of the least significant set bit, 0 if none.
 */

long long ffsll(long long x)
{
    if (x == 0) return 0;

    long long pos = 1;
    while (!(x & 1)) {
        x >>= 1;
        pos++;
    }
    return pos;
}

