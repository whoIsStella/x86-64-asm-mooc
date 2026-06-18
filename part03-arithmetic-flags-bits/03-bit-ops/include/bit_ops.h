#ifndef BIT_OPS_H
#define BIT_OPS_H

/* popcount_and_rotate(x, r)
 *
 * Return popcnt(x) + left_rotate(x, r).
 *
 * popcnt(x)          — count of set bits in x (using the popcnt instruction).
 * left_rotate(x, r)  — rotate x left by r bit positions (using the rol instruction).
 *
 * SysV AMD64: x=rdi (unsigned long), r=esi (int), return unsigned long in rax.
 */
unsigned long popcount_and_rotate(unsigned long x, int r);

#endif
