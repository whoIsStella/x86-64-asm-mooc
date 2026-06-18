#ifndef SIGNED_UNSIGNED_CMP_H
#define SIGNED_UNSIGNED_CMP_H

/* cmp3(a, b)
 *
 * Signed three-way comparison.
 * Returns -1 if a < b, 0 if a == b, 1 if a > b.
 * Uses signed condition codes (jl/jg), NOT unsigned (jb/ja).
 *
 * SysV AMD64: a=rdi, b=rsi, return int in eax.
 */
int cmp3(long a, long b);

#endif
