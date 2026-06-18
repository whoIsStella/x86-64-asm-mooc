.intel_syntax noprefix
.text
.globl lea_scale_add
.type lea_scale_add, @function
lea_scale_add:
    lea rax, [rdi + rsi*8 + 16]
    ret
.size lea_scale_add, .-lea_scale_add
