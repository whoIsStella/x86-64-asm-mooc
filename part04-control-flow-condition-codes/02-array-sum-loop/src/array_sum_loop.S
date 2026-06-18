.intel_syntax noprefix
.text
.globl array_sum
.type array_sum, @function
array_sum:
    # TODO: sum n signed 64-bit longs starting at a.
    # SysV AMD64: a in rdi, n in rsi, return value in rax.
    # Use a counted loop: compare an index to n, branch back while index < n.
    xor rax, rax
    ret
.size array_sum, .-array_sum
