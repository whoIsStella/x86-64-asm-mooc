.intel_syntax noprefix
.text
.globl my_strlen
.type my_strlen, @function
my_strlen:
    # TODO: return the length of the NUL-terminated string at rdi.
    # Use repne scasb: set rdi=s, al=0, rcx=large sentinel,
    # cld to ensure forward scan, then compute length from rcx.
    xor rax, rax
    ret
.size my_strlen, .-my_strlen
