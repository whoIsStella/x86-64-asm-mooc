/* 01-hello-syscall — GREEN solution
 *
 * Writes "hello\n" to stdout via write(2) syscall, then exits 0.
 */
	.intel_syntax noprefix
	.section .rodata
msg:
	.ascii "hello\n"
msg_len = . - msg          /* assembler constant: 6 */

	.text
	.globl _start
_start:
	/* write(1, msg, 6) */
	mov  rax, 1            /* sys_write */
	mov  rdi, 1            /* fd = stdout */
	lea  rsi, [rip + msg]  /* buf */
	mov  rdx, msg_len      /* count = 6 */
	syscall

	/* exit(0) */
	mov  rax, 60           /* sys_exit */
	xor  rdi, rdi          /* status = 0 */
	syscall
