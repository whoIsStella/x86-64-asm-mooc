.intel_syntax noprefix
.text
.globl mixed
.type mixed, @function
mixed:
    # Return a + *p + c.
    # SysV AMD64: a=rdi, p=rsi (pointer to long), c=rdx, return in rax.
    #
    # Dereference p with a memory load, then add the three values.
    mov rax, [rsi]      # rax = *p  (load 8-byte value from address in rsi)
    add rax, rdi        # rax = a + *p
    add rax, rdx        # rax = a + *p + c
    ret
.size mixed, .-mixed
