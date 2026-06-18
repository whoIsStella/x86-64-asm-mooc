/* 02-exit-code — RED stub
 *
 * TODO: Make _start exit with status code 42 via the exit syscall.
 *
 * Hint:
 *   exit syscall : rax=60, rdi=<status>  → syscall
 *
 * The stub exits with 0 (wrong). Change it to 42.
 */
	.intel_syntax noprefix
	.text
	.globl _start
_start:
	/* TODO: exit with code 42 */
	mov  rax, 60          /* exit syscall */
	mov  rdi, 0           /* exit code 0 (wrong: should be 42) */
	syscall
