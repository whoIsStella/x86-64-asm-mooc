    .intel_syntax noprefix
    .text
    .globl popcount_and_rotate
    .type popcount_and_rotate, @function
popcount_and_rotate:
    # SysV AMD64: x=rdi (unsigned long), r=esi (int), return unsigned long in rax
    # popcnt counts set bits; rol rotates left by cl (count register, byte).
    popcnt rax, rdi       # rax = popcount(x)
    mov ecx, esi          # cl = rotation count (rol reads cl for variable shifts)
    rol rdi, cl           # rdi = left_rotate(x, r)
    add rax, rdi          # rax = popcnt(x) + left_rotate(x, r)
    ret
    .size popcount_and_rotate, .-popcount_and_rotate
