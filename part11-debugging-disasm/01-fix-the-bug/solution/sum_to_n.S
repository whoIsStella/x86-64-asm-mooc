/* sum_to_n.S — reference solution.
 *
 * Fix applied: `jge` → `jg` so the loop continues through counter == n,
 * correctly including n in the sum.
 */
.intel_syntax noprefix
.text
.globl sum_to_n
.type  sum_to_n, @function

/* long sum_to_n(long n);
 *   n   -> rdi
 *   rax <- 1 + 2 + ... + n  (0 when n <= 0)
 */
sum_to_n:
    xor  rax, rax          /* accumulator = 0            */
    mov  rcx, 1            /* counter     = 1            */
.loop:
    cmp  rcx, rdi          /* counter vs n               */
    jg   .done             /* exit when counter > n (i.e. loop while counter <= n) */
    add  rax, rcx          /* accumulator += counter     */
    inc  rcx               /* counter++                  */
    jmp  .loop
.done:
    ret
.size sum_to_n, .-sum_to_n
