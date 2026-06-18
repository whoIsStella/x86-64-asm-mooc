/* 03-write-count — RED stub
 *
 * TODO: Write "ABCABCABC" (9 bytes) to stdout, then exit 0.
 *
 * You can use one write call for all 9 bytes, or loop over 3 writes of 3 bytes.
 *
 * Hints:
 *   write syscall : rax=1, rdi=1, rsi=buf, rdx=len  → syscall
 *   exit  syscall : rax=60, rdi=0                   → syscall
 *   syscall clobbers rcx and r11 — use rbx for loop counter.
 *
 * The stub writes nothing and exits 0 (wrong output).
 */
	.intel_syntax noprefix
	.section .rodata
abc:
	.ascii "ABC"
	/* TODO: add more bytes or use a loop */

	.text
	.globl _start
_start:
	/* TODO: write "ABCABCABC" to stdout */

	/* Stub: skip the write, just exit 0 (wrong: no output) */
	mov  rax, 60          /* exit syscall */
	xor  rdi, rdi         /* exit code 0 */
	syscall
