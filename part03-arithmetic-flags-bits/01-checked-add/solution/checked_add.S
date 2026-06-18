    .intel_syntax noprefix
    .text
    .globl checked_add
    .type checked_add, @function
checked_add:
    # SysV AMD64: a=rdi, b=rsi, out=rdx, return int in eax
    # add sets OF (overflow flag) if signed overflow occurs.
    add rdi, rsi          # rdi = a + b; OF set on signed overflow
    mov [rdx], rdi        # store result into *out
    seto al               # al = 1 if OF set, else 0
    movzx eax, al         # zero-extend to eax (clears upper 32 bits)
    ret
    .size checked_add, .-checked_add
