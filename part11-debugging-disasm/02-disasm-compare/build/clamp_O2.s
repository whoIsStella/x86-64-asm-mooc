	.file	"reference.c"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	clamp
	.type	clamp, @function
clamp:
.LFB0:
	.cfi_startproc
	cmp	edi, edx
	mov	eax, esi
	cmovle	edx, edi
	cmp	edi, esi
	cmovge	eax, edx
	ret
	.cfi_endproc
.LFE0:
	.size	clamp, .-clamp
	.ident	"GCC: (Debian 14.2.0-19) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
