.intel_syntax noprefix
.text
.globl sum_static
.type sum_static, @function
sum_static:
    # TODO: load the static array via RIP-relative addressing and sum it.
    # The array {10, 20, 30, 40, 50} lives in .rodata in solution/sum_static.S.
    # Return the sum in rax.
    xor rax, rax
    ret
.size sum_static, .-sum_static
