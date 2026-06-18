.intel_syntax noprefix
.text
.globl my_memcpy
.type my_memcpy, @function
my_memcpy:
    # TODO: copy rcx bytes from rsi (src) to rdi (dst) using rep movsb.
    # SysV AMD64: dst in rdi, src in rsi, n in rdx.
    # Hint: mov rcx, rdx  then  cld  then  rep movsb.
    ret
.size my_memcpy, .-my_memcpy
