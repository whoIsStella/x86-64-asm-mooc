.intel_syntax noprefix
.text
.globl imax
.type imax, @function
imax:
    # Start with rax = b (rsi); conditionally replace with a (rdi) if a > b.
    mov rax, rsi
    cmp rdi, rsi
    cmovg rax, rdi
    ret
.size imax, .-imax
