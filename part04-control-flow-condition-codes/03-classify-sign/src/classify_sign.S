.intel_syntax noprefix
.text
.globl classify
.type classify, @function
classify:
    # TODO: return -1 if x < 0, 0 if x == 0, 1 if x > 0.
    # SysV AMD64: x in rdi, return value in eax (int).
    # Use a jump ladder: cmp rdi, 0  then jl/je/jg.
    xor eax, eax
    ret
.size classify, .-classify
