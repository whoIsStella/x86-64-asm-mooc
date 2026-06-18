/* 01-hello-syscall — RED stub
 *
 * TODO: Make _start write "hello\n" to stdout via the write syscall,
 *       then exit with code 0 via the exit syscall.
 *
 * Hints:
 *   write syscall : rax=1, rdi=fd(1), rsi=buf, rdx=len(6)  → syscall
 *   exit  syscall : rax=60, rdi=0                           → syscall
 *
 * The string literal belongs in .rodata (or .data), not in .text.
 */
	.intel_syntax noprefix
	.section .rodata
msg:
	/* TODO: define your "hello\n" bytes here */

	.text
	.globl _start
_start:
	/* TODO: call write(1, msg, 6) */
	/* TODO: call exit(0) */

	/* Stub falls through — exits with wrong code, no output */
	mov  rax, 60          /* exit syscall */
	mov  rdi, 1           /* exit code 1 (wrong: should be 0) */
	syscall
