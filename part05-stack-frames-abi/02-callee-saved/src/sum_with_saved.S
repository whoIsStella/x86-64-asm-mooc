.intel_syntax noprefix
.text
.globl sum_with_saved
.type sum_with_saved, @function
sum_with_saved:
    # TODO: compute a + b + c + d using callee-saved registers.
    # SysV AMD64: a=rdi, b=rsi, c=rdx, d=rcx, return in rax.
    # You MUST save any callee-saved register (rbx, r12-r15) you use:
    #   push <reg> at entry, pop <reg> before ret.
    # This stub returns 0 (wrong), so all tests fail.
    xor rax, rax
    ret
.size sum_with_saved, .-sum_with_saved
