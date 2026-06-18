/* 03-write-count — GREEN solution
 *
 * Writes "ABCABCABC" (9 bytes) using a loop of 3 write(2) syscalls,
 * then exits 0.
 *
 * syscall clobbers rcx and r11; loop counter lives in rbx.
 */
	.intel_syntax noprefix
	.section .rodata
abc:
	.ascii "ABC"

	.text
	.globl _start
_start:
	mov  rbx, 3               /* loop counter: 3 iterations */
.Lloop:
	mov  rax, 1               /* sys_write */
	mov  rdi, 1               /* fd = stdout */
	lea  rsi, [rip + abc]     /* buf = "ABC" */
	mov  rdx, 3               /* count = 3 bytes */
	syscall

	dec  rbx
	jnz  .Lloop

	/* exit(0) */
	mov  rax, 60              /* sys_exit */
	xor  rdi, rdi             /* status = 0 */
	syscall
