.intel_syntax noprefix
.text
.globl classify
.type classify, @function
classify:
    # rdi = x; return int in eax.
    cmp rdi, 0
    jl  .Lneg
    je  .Lzero
    # falls through: x > 0
    mov eax, 1
    ret
.Lneg:
    mov eax, -1
    ret
.Lzero:
    xor eax, eax
    ret
.size classify, .-classify
