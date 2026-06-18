    .intel_syntax noprefix
    .text
    .globl checked_add
    .type checked_add, @function
checked_add:
    # TODO: implement checked_add
    # SysV AMD64: a=rdi, b=rsi, out=rdx, return int in eax
    # Compute rdi+rsi into [rdx], return 1 if signed overflow else 0.
    xor eax, eax   # wrong: always returns 0 (never signals overflow)
    ret
    .size checked_add, .-checked_add
