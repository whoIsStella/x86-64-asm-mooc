.intel_syntax noprefix
.text
.globl mixed
.type mixed, @function
mixed:
    # TODO: return a + *p + c.
    # SysV AMD64: a=rdi, p=rsi (pointer to long), c=rdx, return in rax.
    # Load the value at the address in rsi with: mov rax, [rsi]
    xor rax, rax
    ret
.size mixed, .-mixed
