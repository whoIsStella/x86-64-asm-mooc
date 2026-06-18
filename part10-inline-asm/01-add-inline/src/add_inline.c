#include "add_inline.h"

/*
 * TODO: implement add_inline(a, b) using GCC extended inline assembly.
 *
 * The asm template should be:  addq %1, %0
 * Hint: tie the input `a` to output operand 0 so that the instruction
 * reads and writes the same register.
 *
 * This stub returns a - b (wrong) so that the tests deterministically fail.
 */
long add_inline(long a, long b)
{
    return a - b;   /* BUG: subtraction instead of addition */
}
