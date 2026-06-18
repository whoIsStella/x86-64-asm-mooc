/* fixed.S — corrected implementation for the ABI forensic exercise.
 *
 * Fixes applied:
 *   1. rbx is pushed on entry and popped before ret (callee-save contract).
 *   2. The arithmetic now computes a*2 + b correctly.
 *
 * Note: we could avoid rbx entirely by keeping everything in rdi/rax, but
 * the point of this exercise is to show the correct push/pop pattern.
 */
.intel_syntax noprefix
.text
.globl broken_abi
.type  broken_abi, @function

/* long broken_abi(long a, long b);
 *   a -> rdi,  b -> rsi
 *   returns a*2 + b
 */
broken_abi:
    push rbx               /* save callee-saved register                    */
    mov  rbx, rdi          /* rbx = a                                       */
    add  rbx, rbx          /* rbx = a*2  (same as shl rbx, 1)               */
    add  rbx, rsi          /* rbx = a*2 + b                                 */
    mov  rax, rbx          /* return value                                  */
    pop  rbx               /* restore callee-saved register                 */
    ret
.size broken_abi, .-broken_abi
