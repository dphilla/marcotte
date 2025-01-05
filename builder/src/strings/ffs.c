/**
 * ffs.c
 *
 * Finds the first (least significant) bit set in 'i',
 * returning the 1-based index of that bit. Returns 0 if i == 0.
 */

int ffs(int i)
{
    if (i == 0) return 0;

    int pos = 1;
    while (!(i & 1)) {
        i >>= 1;
        pos++;
    }
    return pos;
}

