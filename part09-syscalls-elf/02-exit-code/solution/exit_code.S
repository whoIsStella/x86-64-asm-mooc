/* 02-exit-code — GREEN solution
 *
 * Exits with status code 42.
 */
	.intel_syntax noprefix
	.text
	.globl _start
_start:
	mov  rax, 60          /* sys_exit */
	mov  rdi, 42          /* status = 42 */
	syscall
