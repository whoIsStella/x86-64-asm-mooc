.intel_syntax noprefix
.text
.globl my_memcpy
.type my_memcpy, @function
my_memcpy:
    # SysV AMD64: dst in rdi, src in rsi, n in rdx
    #
    # rep movsb copies rcx bytes from [rsi] to [rdi], advancing both
    # pointers by 1 each iteration.  Direction is controlled by DF:
    # DF=0 (forward) is required by the SysV ABI on entry and exit.
    #
    mov rcx, rdx    # rcx = n (byte count)
    cld             # DF=0: copy forward (ABI requirement)
    rep movsb       # copy rcx bytes from [rsi] to [rdi]
    ret
.size my_memcpy, .-my_memcpy
