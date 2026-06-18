.intel_syntax noprefix
.text
.globl lea_scale_add
.type lea_scale_add, @function
lea_scale_add:
    # TODO: return base + index * 8 + 16.
    # SysV AMD64: base in rdi, index in rsi, return in rax.
    xor rax, rax
    ret
.size lea_scale_add, .-lea_scale_add
