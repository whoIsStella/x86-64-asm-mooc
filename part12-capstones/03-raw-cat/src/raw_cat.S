/* raw_cat stub — exits 0 immediately without reading or writing anything.
 * The test FAILS because no output is produced (expected == input).
 *
 * TODO: implement a read/write loop:
 *   1. Allocate a stack buffer (e.g. sub rsp, 4096)
 *   2. Loop:
 *      a. read(0, buf, 4096) -> rax; if rax <= 0, break (EOF or error)
 *      b. write(1, buf, rax) -- loop on partial writes (rax may be < requested)
 *   3. exit(0)
 *
 * Syscall numbers (Linux x86-64):
 *   SYS_read  = 0   args: rdi=fd(0), rsi=buf, rdx=count  -> bytes read
 *   SYS_write = 1   args: rdi=fd(1), rsi=buf, rdx=count  -> bytes written
 *   SYS_exit  = 60  args: rdi=exit_code
 */

.intel_syntax noprefix
.text
.globl _start
.type _start, @function

_start:
    /* TODO: implement the read->write loop (see comments above).
     * Currently just exits without writing anything. */
    mov     eax, 60     /* SYS_exit */
    xor     edi, edi    /* exit code 0 */
    syscall
.size _start, .-_start
