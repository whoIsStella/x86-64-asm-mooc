/* sum_to_n.S — BUGGY stub for the fix-the-bug exercise.
 *
 * Bug: the exit branch uses `jge` (jump if counter >= n) so the final
 * iteration where counter == n is skipped.  The loop runs while counter < n
 * instead of counter <= n.
 *
 * Example: sum_to_n(5) returns 1+2+3+4 = 10 instead of 1+2+3+4+5 = 15.
 *
 * Your task:
 *   1. Run `make test` and observe the failures.
 *   2. Open gdb, set a breakpoint at sum_to_n, step through with `stepi`,
 *      and watch rcx / rax with `info registers` after each iteration.
 *   3. Use `objdump -d -M intel build/test_stub` to spot the wrong branch.
 *   4. Change `jge` to `jg` below (or equivalently change `jl` to `jle`).
 *   5. Run `make test` again — all tests should turn GREEN.
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
    jge  .done             /* BUG: exits when counter >= n, should be jg */
    add  rax, rcx          /* accumulator += counter     */
    inc  rcx               /* counter++                  */
    jmp  .loop
.done:
    ret
.size sum_to_n, .-sum_to_n
