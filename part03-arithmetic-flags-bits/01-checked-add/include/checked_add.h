#ifndef CHECKED_ADD_H
#define CHECKED_ADD_H

/* checked_add(a, b, out)
 *
 * Compute a + b and store the result in *out.
 * Returns 1 if signed overflow occurred (overflow flag set), 0 otherwise.
 *
 * SysV AMD64: a=rdi, b=rsi, out=rdx, return int in eax.
 */
int checked_add(long a, long b, long *out);

#endif
