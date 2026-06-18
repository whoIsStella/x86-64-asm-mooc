#include "negate_all.h"

/*
 * TODO: implement negate_all using GCC extended inline assembly.
 *
 * Loop over arr[0..n-1] and apply:
 *     asm volatile ("negq %0" : "+m"(arr[i]) : : "cc");
 *
 * Key constraints to use:
 *   "+m"(arr[i])  — read-write memory operand (negq reads and writes)
 *   "cc"          — negq modifies EFLAGS
 *   volatile      — ensures the asm is not elided by the optimiser
 *
 * This stub does nothing — it returns without modifying the array,
 * so all tests will deterministically fail.
 */
void negate_all(long *arr, long n)
{
    (void)arr;  /* BUG: array is never modified */
    (void)n;
}
