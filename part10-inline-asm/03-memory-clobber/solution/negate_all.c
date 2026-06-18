#include "negate_all.h"

/*
 * Reference solution — negate_all using negq via inline asm.
 *
 * Constraint breakdown:
 *   "+m"(arr[i])  — read-write memory operand.
 *                   "m"  : operand lives in memory (no register needed).
 *                   "+"  : operand is both read and written by the asm.
 *                   negq reads the value, negates it, and writes it back
 *                   to the same address.
 *
 *   "cc"          — negq sets CF, ZF, SF, OF, PF; declare the clobber so
 *                   GCC does not assume EFLAGS is unchanged across the asm.
 *
 *   volatile      — prevents GCC from eliding asm statements that have
 *                   side effects not fully captured by the operand list.
 *                   With "+m" the side effect IS captured, but volatile
 *                   is good defensive practice for memory-writing asm.
 */
void negate_all(long *arr, long n)
{
    for (long i = 0; i < n; i++) {
        asm volatile ("negq %0"
                      : "+m"(arr[i])
                      :
                      : "cc");
    }
}
