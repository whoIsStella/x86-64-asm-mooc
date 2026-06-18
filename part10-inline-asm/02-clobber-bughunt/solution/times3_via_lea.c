#include "times3_via_lea.h"

/*
 * Reference solution — times3_via_lea using leaq.
 *
 * leaq (%src, %src, 2), %dst  computes  dst = src + src*2 = src*3
 *
 * Constraint notes:
 *   "=r"(result)  — fresh output register (lea writes, does not read dst)
 *   "r"(x)        — input in any GP register
 *
 * No "cc" clobber needed: leaq does not modify EFLAGS.
 * No tied operand needed: lea produces a new value in a separate register.
 */
long times3_via_lea(long x)
{
    long result;
    asm("leaq (%1,%1,2), %0"
        : "=r"(result)
        : "r"(x)
        );
    return result;
}
