#ifndef VECTOR_ADD4_H
#define VECTOR_ADD4_H

/* Add four packed single-precision floats element-wise.
 * dst[i] = a[i] + b[i]  for i in 0..3
 * All pointers must point to at least 4 floats (16 bytes).
 */
void add4_floats(float *dst, const float *a, const float *b);

#endif
