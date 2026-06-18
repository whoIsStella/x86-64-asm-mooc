    .intel_syntax noprefix
    .text
    .globl popcount_and_rotate
    .type popcount_and_rotate, @function
popcount_and_rotate:
    # TODO: implement popcount_and_rotate
    # SysV AMD64: x=rdi (unsigned long), r=esi (int), return unsigned long in rax
    # Return popcnt(x) + left_rotate(x, r).
    xor eax, eax   # wrong: always returns 0
    ret
    .size popcount_and_rotate, .-popcount_and_rotate
