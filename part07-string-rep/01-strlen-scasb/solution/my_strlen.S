.intel_syntax noprefix
.text
.globl my_strlen
.type my_strlen, @function
my_strlen:
    # rdi = s (pointer to NUL-terminated string)
    #
    # repne scasb compares AL with [rdi], increments rdi, decrements rcx,
    # and repeats while ZF==0 (no match) and rcx!=0.
    # It stops when it finds AL in [rdi] (the NUL byte).
    #
    # With rcx_init = 0xFFFFFFFFFFFFFFFF (-1 unsigned):
    #   iterations consumed = length + 1  (length chars + the NUL)
    #   rcx_after = rcx_init - (length + 1)
    #
    # Therefore:
    #   ~rcx_after = ~(rcx_init - length - 1)
    #              = length + 1            (since ~(N-k) = k-1 when N=0xFF..FF)
    #   length     = ~rcx_after - 1
    #
    cld                     # DF=0: scan forward (required by SysV ABI)
    xor eax, eax            # al = 0 (the NUL sentinel)
    mov rcx, -1             # large sentinel; will count down
    repne scasb             # scan [rdi]++ until al found; rcx--
    not rcx                 # rcx = length + 1
    lea rax, [rcx - 1]      # rax = length
    ret
.size my_strlen, .-my_strlen
