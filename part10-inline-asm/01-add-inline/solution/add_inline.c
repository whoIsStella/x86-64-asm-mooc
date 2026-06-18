#include "add_inline.h"

/*
 * Reference solution — add_inline using GCC extended inline assembly.
 *
 * Constraint breakdown:
 *   "+r"(result)   — read-write: GCC picks a register, loads `a` into it
 *                    before the asm runs, then reads it back after.
 *                    The "+" modifier means the operand is both an input
 *                    and an output — exactly what addq requires (it reads
 *                    the destination before writing it).
 *   "r"(b)         — input: b in any GP register.
 *   "cc"           — addq modifies EFLAGS; declare the clobber.
 *
 * Alternative with a tied operand ("0"):
 *   asm("addq %2, %0" : "=r"(result) : "0"(a), "r"(b) : "cc");
 * Here %0 = result (output), %1/%0 = a (tied to output 0), %2 = b.
 * "addq %2, %0" adds b into the a/result register — also correct, but
 * the "+r" form below is more idiomatic and less error-prone.
 */
long add_inline(long a, long b)
{
    long result = a;
    asm("addq %1, %0"
        : "+r"(result)
        : "r"(b)
        : "cc");
    return result;
}
