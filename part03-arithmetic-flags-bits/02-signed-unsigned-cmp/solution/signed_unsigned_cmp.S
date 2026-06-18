    .intel_syntax noprefix
    .text
    .globl cmp3
    .type cmp3, @function
cmp3:
    # SysV AMD64: a=rdi, b=rsi, return int in eax
    # cmp sets SF, OF, ZF based on rdi - rsi (signed subtraction).
    # jl  = jump if less     (SF != OF)
    # jg  = jump if greater  (ZF == 0 and SF == OF)
    xor eax, eax          # assume equal (eax = 0)
    cmp rdi, rsi          # set flags from rdi - rsi
    jl  .Lless            # signed less: SF != OF
    jg  .Lgreater         # signed greater: ZF=0, SF=OF
    ret                   # equal: eax already 0
.Lless:
    mov eax, -1
    ret
.Lgreater:
    mov eax, 1
    ret
    .size cmp3, .-cmp3
