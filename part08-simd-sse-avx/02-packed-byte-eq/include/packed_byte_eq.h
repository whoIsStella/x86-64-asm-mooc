#ifndef PACKED_BYTE_EQ_H
#define PACKED_BYTE_EQ_H

/* Compare 16 bytes of a[] and b[] simultaneously using SSE2.
 * Returns the number of positions i (0..15) where a[i] == b[i].
 */
int count_equal_bytes(const unsigned char *a, const unsigned char *b);

#endif
