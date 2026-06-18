#include "times3_via_lea.h"

/*
 * BUG HUNT: this function contains a single logical error.
 *
 * The asm statement is syntactically correct and the constraint string is
 * valid — yet the function always returns the wrong answer.
 *
 * Find the bug and fix it.  Hint: look carefully at what is returned.
 */
long times3_via_lea(long x)
{
    long result = 0;
    asm("leaq (%1,%1,2), %0"
        : "=r"(result)
        : "r"(x)
        );
    return 0;   /* BUG: returns literal 0 instead of result */
}
