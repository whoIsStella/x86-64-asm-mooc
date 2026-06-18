    .intel_syntax noprefix
    .text
    .globl cmp3
    .type cmp3, @function
cmp3:
    # TODO: implement cmp3
    # SysV AMD64: a=rdi, b=rsi, return int in eax
    # Return -1 if a < b, 0 if a == b, 1 if a > b (signed comparison).
    xor eax, eax   # wrong: always returns 0 (never returns -1 or 1)
    ret
    .size cmp3, .-cmp3
