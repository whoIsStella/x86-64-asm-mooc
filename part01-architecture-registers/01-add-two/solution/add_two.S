.intel_syntax noprefix
.text
.globl add_two
.type add_two, @function
add_two:
    lea rax, [rdi + rsi]
    ret
.size add_two, .-add_two
