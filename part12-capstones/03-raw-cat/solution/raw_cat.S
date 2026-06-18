/* raw_cat — freestanding (no libc) stdin->stdout loop, then exit(0).
 *
 * Syscalls used (Linux x86-64):
 *   read (0):  rax=0, rdi=0 (stdin), rsi=buf, rdx=buflen  -> bytes read (0=EOF, <0=error)
 *   write(1):  rax=1, rdi=1 (stdout), rsi=buf, rdx=bytes  -> bytes written (may be partial)
 *   exit (60): rax=60, rdi=0
 *
 * Partial-write handling: write() may return fewer bytes than requested
 * (e.g. if stdout is a pipe that fills), so we loop until all bytes are written.
 */

.intel_syntax noprefix
.text
.globl _start
.type _start, @function

_start:
    /* Reserve a 4096-byte buffer on the stack.
     * rsp is 16-byte aligned at process start; 4096 keeps that alignment. */
    sub     rsp, 4096

.Lread_loop:
    /* read(0, rsp, 4096) */
    xor     eax, eax            /* rax = 0 (SYS_read) */
    xor     edi, edi            /* rdi = 0 (stdin fd) */
    mov     rsi, rsp            /* rsi = buffer */
    mov     edx, 4096           /* rdx = count */
    syscall

    test    rax, rax
    jz      .Lexit              /* rax == 0: EOF */
    js      .Lexit              /* rax < 0:  error, treat as EOF */

    /* rax = bytes read. Write them all to stdout (fd 1).
     * Loop to handle partial writes. */
    mov     r8, rax             /* r8 = total bytes remaining to write */
    mov     r9, rsp             /* r9 = write pointer */

.Lwrite_loop:
    mov     eax, 1              /* rax = 1 (SYS_write) */
    mov     edi, 1              /* rdi = 1 (stdout fd) */
    mov     rsi, r9             /* rsi = current buffer position */
    mov     rdx, r8             /* rdx = remaining byte count */
    syscall

    test    rax, rax
    jle     .Lexit              /* write error or 0 bytes: exit */

    sub     r8, rax             /* r8 -= bytes written */
    add     r9, rax             /* advance pointer */
    jnz     .Lwrite_loop        /* if r8 != 0, more bytes to write */

    jmp     .Lread_loop         /* read next chunk */

.Lexit:
    /* exit(0) */
    mov     eax, 60             /* rax = 60 (SYS_exit) */
    xor     edi, edi            /* rdi = 0 (exit code) */
    syscall
.size _start, .-_start
