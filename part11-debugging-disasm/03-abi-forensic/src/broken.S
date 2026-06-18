/* broken.S — ABI-violating function for the forensic exercise.
 *
 * This function is supposed to return  a*2 + b  but it:
 *
 *   1. Returns the WRONG value (a + b instead of a*2 + b).
 *   2. Clobbers the callee-saved register rbx without saving/restoring it,
 *      which violates the SysV AMD64 ABI.
 *
 * Your task:
 *   - Run `make test` and observe the failures.
 *   - Use `objdump -d -M intel build/test_broken` to inspect the code.
 *   - Notice that rbx is written (mov rbx, rdi) but never push/pop-ed.
 *   - Notice the arithmetic computes a + b, not a*2 + b.
 *   - Fill in report.md, then look at solution/fixed.S and run `make solve`.
 */
.intel_syntax noprefix
.text
.globl broken_abi
.type  broken_abi, @function

/* long broken_abi(long a, long b);
 *   a -> rdi,  b -> rsi
 *   should return a*2 + b
 *
 * BUG 1: uses rbx (callee-saved) without push/pop
 * BUG 2: computes a + b instead of a*2 + b
 */
broken_abi:
    mov  rbx, rdi          /* BUG: clobbers callee-saved rbx, no push first */
    add  rbx, rsi          /* BUG: adds b (should double a first)           */
    mov  rax, rbx          /* return value = a + b  (wrong)                 */
    ret
.size broken_abi, .-broken_abi
