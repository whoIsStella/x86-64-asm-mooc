.intel_syntax noprefix
.text
.globl imax
.type imax, @function
imax:
    # TODO: return the greater of a (rdi) and b (rsi) using cmp + cmovg.
    # SysV AMD64: a in rdi, b in rsi, return value in rax.
    xor rax, rax
    ret
.size imax, .-imax
