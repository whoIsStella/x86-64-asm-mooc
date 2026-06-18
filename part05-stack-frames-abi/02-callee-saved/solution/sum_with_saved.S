.intel_syntax noprefix
.text
.globl sum_with_saved
.type sum_with_saved, @function
sum_with_saved:
    # Compute a + b + c + d using callee-saved registers rbx and r12.
    # SysV AMD64: a=rdi, b=rsi, c=rdx, d=rcx, return in rax.
    #
    # We save rbx and r12 (callee-saved) at entry, use them for
    # intermediate storage, then restore before returning.

    push rbx            # save callee-saved rbx
    push r12            # save callee-saved r12
    # Stack is now 16-byte aligned (two 8-byte pushes from 8-mod-16 entry).

    mov rbx, rdi        # rbx = a
    mov r12, rsi        # r12 = b
    add rbx, r12        # rbx = a + b
    add rbx, rdx        # rbx = a + b + c
    add rbx, rcx        # rbx = a + b + c + d
    mov rax, rbx        # return value

    pop r12             # restore r12
    pop rbx             # restore rbx
    ret
.size sum_with_saved, .-sum_with_saved
